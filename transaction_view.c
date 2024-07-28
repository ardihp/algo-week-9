#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/fort.h"
#include "transaction.h"
#include "transaction_struct.h"



BookSaleTransactionList getAllTransactions(){
    FILE *TransactionDBConnection;
    char row[1000];
    BookSaleTransactionList bookTransactionList;
    bookTransactionList.total_transaction = 0;
    TransactionDBConnection = fopen(TRX_DB_FILE, "r");

    if (TransactionDBConnection == NULL)
    {
        perror("Gagal membuka file data transaksi");
        return bookTransactionList;
    }
    else
    {
        int index = 0;
        while (fgets(row, 1000, TransactionDBConnection))
        {
            BookSaleTransaction bookTransaction;
            char *token = strtok(row, ",");
            bookTransaction.trx_id = atoi(token);
            strcpy(bookTransaction.buyer_name, strtok(NULL, ","));
            strcpy(bookTransaction.book_id, strtok(NULL, ","));
            strcpy(bookTransaction.book_name, strtok(NULL, ","));
            strcpy(bookTransaction.book_category, strtok(NULL, ","));
            bookTransaction.book_price = atoi(strtok(NULL, ","));
            bookTransaction.book_qty = atoi(strtok(NULL, ","));
            bookTransaction.value = atof(strtok(NULL, ","));

            bookTransactionList.data[index] = bookTransaction;
            bookTransactionList.total_transaction++;
            index++;
        }

        fclose(TransactionDBConnection);
    }

    return bookTransactionList;
}


BookSaleTransaction getTransactionById(char* transactionCode){
    FILE *TransactionDBConnection;
    char row[1000];
    BookSaleTransaction bookTransaction;
    bookTransaction.trx_id = -1;
    TransactionDBConnection = fopen(TRX_DB_FILE, "r");

    if (TransactionDBConnection == NULL)
    {
        perror("Gagal membuka file data transaksi");
        return bookTransaction;
    }
    else
    {
        while (fgets(row, 1000, TransactionDBConnection))
        {
            char *token = strtok(row, ",");
            if(strcmp(token, transactionCode) == 0){
                bookTransaction.trx_id = atoi(token);
                strcpy(bookTransaction.buyer_name, strtok(NULL, ","));
                strcpy(bookTransaction.book_id, strtok(NULL, ","));
                strcpy(bookTransaction.book_name, strtok(NULL, ","));
                strcpy(bookTransaction.book_category, strtok(NULL, ","));
                bookTransaction.book_price = atoi(strtok(NULL, ","));
                bookTransaction.book_qty = atoi(strtok(NULL, ","));
                bookTransaction.value = atof(strtok(NULL, ","));
                break;
            }
        }

        fclose(TransactionDBConnection);
    }

    return bookTransaction;
}





int viewAllTransactions()
{
      /* Setup Table */
    ft_table_t *table = ft_create_table();
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "TRX ID", "Buyer Name", "Book ID", "Book Name", "Book Category", "Price", "Qty", "Value");


    char row[1000];   
    int totalTransaction = 0;
    int ch;

    printf("Menampilkan semua data transaksi\n");
    printf("=================================\n");

    BookSaleTransactionList bookTransactionList = getAllTransactions();
    totalTransaction = bookTransactionList.total_transaction;

    for(int i = 0; i < totalTransaction; i++){
        BookSaleTransaction bookTransaction = bookTransactionList.data[i];
        char trx_id_str[100];
        sprintf(trx_id_str, "%d", bookTransaction.trx_id);
        char book_price_str[100];
        sprintf(book_price_str, "%d", bookTransaction.book_price);
        char book_qty_str[100];
        sprintf(book_qty_str, "%d", bookTransaction.book_qty);
        char value_str[100];
        sprintf(value_str, "%f", bookTransaction.value);

        ft_write_ln(table, trx_id_str, bookTransaction.buyer_name, bookTransaction.book_id, bookTransaction.book_name, bookTransaction.book_category, book_price_str, book_qty_str, value_str);
    }


    if (totalTransaction < 1)
    {
            printf("Tidak ada data transaksi yang tersedia\n");
    } else
    {
            printf("%s\n", ft_to_string(table));  
    }
    ft_destroy_table(table);
    printf("\n");
}
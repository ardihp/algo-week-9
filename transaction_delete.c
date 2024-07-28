#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "transaction.h"
#include "transaction_struct.h"

int deleteTransaction()
{
    FILE *list_buku;
    FILE *temp_list;
    char combine[1000], ch;
    int jumlah_buku = 0, index_buku;

    BookSaleTransactionList books = getAllTransactions();

    printf("=================================\n");
    viewAllTransactions();
    printf("=================================\n");

    int isInputValid = 0;

    printf("Masukkan kode transaksi yang ingin dihapus: ");
    char trx_code[256];
    scanf("%s", trx_code);


    BookSaleTransaction bookTransaction = getTransactionById(trx_code);
    if(bookTransaction.trx_id == -1){
        printf("Transaksi tidak ditemukan\n");
        
    }else{
        isInputValid = 1;
    }
    while (!isInputValid)
    {
        printf("Transaksi dengan kode '%s' tidak ditemukan\n", trx_code);
        printf("Masukkan kode transaksi yang ingin dihapus: ");
        scanf("%s", trx_code);
        bookTransaction = getTransactionById(trx_code);
        if(bookTransaction.trx_id != -1){
            isInputValid = 1;
        }
        
    }
    

    
    
  

 

    

    char confirm_input;
    printf("Apakah anda yakin ingin menghapus transaksi ini? (y/n): ");
    scanf(" %c", &confirm_input);

    if(confirm_input == 'y'){
        list_buku = fopen(TRX_DB_FILE, "r");
        temp_list = fopen(TRX_DB_TEMP_FILE, "w");

        if (list_buku == NULL)
        {
            perror("Gagal membuka file data transaksi");
            return 1;
        }

        if (temp_list == NULL)
        {
            perror("Gagal membuka file temp transaksi");
            fclose(list_buku);
            return 1;
        }

        while (fgets(combine, 1000, list_buku))
        {
            char current_combine[1000];
            strcpy(current_combine, combine);
            
            
            char currentTrxId[256];
            strcpy(currentTrxId, strtok(current_combine, ","));

            int trx_id = atoi(currentTrxId);
         


            if (bookTransaction.trx_id != trx_id)
            {
                fputs(combine, temp_list);
            }
        }

        fclose(list_buku);
        fclose(temp_list);

        remove(TRX_DB_FILE);
        rename(TRX_DB_TEMP_FILE, TRX_DB_FILE);

        printf("Transaksi berhasil dihapus\n");
        viewAllTransactions();
    }else{
        printf("Batal menghapus Transaksi\n");
    }
}
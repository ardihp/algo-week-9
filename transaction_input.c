#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "transaction_struct.h"
#include "transaction.h"
#include "book.h"




// Declare the function from transaction_struct.c
BookSaleTransaction createBookTransaction(int id, const char* buyer_name, const char* book_id, const char* book_name, const char* book_category, int book_price, int book_qty, float value);


float getTotalTransactionValue(int book_qty, int book_price){
    return book_qty * book_price;
}   

FILE *openTransactionDB()
{
    FILE *transaction_db = fopen(TRX_DB_FILE, "a");
    if (transaction_db == NULL)
    {
        perror("Gagal membuka file data transaksi");
        return NULL;
    }
    return transaction_db;
}


void closeTransactionDB(FILE *transaction_db)
{
    fclose(transaction_db);
}

int inputBookTransaction()
{
    FILE *transaction_db;
    BookSaleTransaction bookTrx;
    srand(time(0));

    printf("===================================\n");
    printf("Masukkan nama pembeli: ");
    
    char buyer_name[100];
    fgets(buyer_name, sizeof(buyer_name), stdin);
    buyer_name[strcspn(buyer_name, "\n")] = 0;

    printf("Masukkan ID buku: ");
    char book_id[100];
    fgets(book_id, sizeof(book_id), stdin);
    book_id[strcspn(book_id, "\n")] = 0;


    int isBookExist = 0;
    Book book = getBukuByKodeBuku(book_id);
    if(book.id != -1){
        isBookExist = 1;
    }

    while (isBookExist == 0)
    {
        printf("Buku dengan kode buku %s tidak ditemukan\n", book_id);
        printf("Masukkan ID buku: ");
        fgets(book_id, sizeof(book_id), stdin);
        book_id[strcspn(book_id, "\n")] = 0;

        book = getBukuByKodeBuku(book_id);
        if(book.id != -1){
            isBookExist = 1;
        }
    }


    printf("Masukkan Jumlah buku: ");
    char book_qty[50];
    fgets(book_qty, sizeof(book_qty), stdin);


    int isQtyValid = 0;
    if(atoi(book_qty) <= book.jumlah_buku){
            isQtyValid = 1;
    }

    while (isQtyValid == 0)
    {
        printf("Jumlah buku yang dimasukkan tidak valid\n");
        printf("Masukkan Jumlah buku: ");
        fgets(book_qty, sizeof(book_qty), stdin);

      
        if(atoi(book_qty) <= book.jumlah_buku){
                isQtyValid = 1;
        }
        
    }


    float totalValue = getTotalTransactionValue(atoi(book_qty), book.harga_buku);
    transaction_db = openTransactionDB();
    bookTrx = createBookTransaction(rand(), buyer_name, book_id, book.nama_buku, book.jenis_buku, book.harga_buku, atoi(book_qty), totalValue);

    // kurangin stock buku
    book.jumlah_buku -= atoi(book_qty);
    updateBook(book);


    fprintf(transaction_db, "%d,%s,%s,%s,%s,%d,%d,%f\n", bookTrx.trx_id, bookTrx.buyer_name, bookTrx.book_id, bookTrx.book_name, bookTrx.book_category, bookTrx.book_price, bookTrx.book_qty, bookTrx.value);

    closeTransactionDB(transaction_db);

    printf("Data successfully created..\n\n");

    return 0;
    
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "transaction.h"
#include "transaction_struct.h"

int deleteTransaction()
{
    FILE *list_transaction;
    FILE *temp_list;
    char combine[1000], ch;
    int jumlah_transaksi = 0, index_transaksi;

    BookSaleTransactionList books = getAllTransactions();

    viewAllTransactions();
    printf("===================================\n");

    list_transaction = fopen(TRX_DB_FILE, "r");

    if (list_transaction == NULL)
    {
        perror("Gagal membuka file data transaksi");
        return 1;
    }
    else
    {

        while (fgets(combine, 1000, list_transaction))
        {
            jumlah_transaksi++;
        }
        printf("Jumlah transaksi yang tersedia: %d buah\n", jumlah_transaksi);

        do
        {
            printf("Masukan index transaksi yang mau kamu hapus (1 ~ %d): ", jumlah_transaksi);
            scanf("%d", &index_transaksi);

            if (index_transaksi < 1 || index_transaksi > jumlah_transaksi)
            {
                printf("Harap masukan index transaksi antara (1 ~ %d)\n", jumlah_transaksi);
            }

        } while (index_transaksi < 1 || index_transaksi > jumlah_transaksi);

        fclose(list_transaction);
    }

    char confirm_input;
    printf("Apakah anda yakin ingin menghapus transaksi ini? (y/n): ");
    scanf(" %c", &confirm_input);

    if (confirm_input == 'y')
    {
        list_transaction = fopen(TRX_DB_FILE, "r");
        temp_list = fopen(TRX_DB_TEMP_FILE, "w");

        if (list_transaction == NULL)
        {
            perror("Gagal membuka file data transaksi");
            return 1;
        }

        if (temp_list == NULL)
        {
            perror("Gagal membuka file temp transaksi");
            fclose(list_transaction);
            return 1;
        }

        int list_index = 1;
        while (fgets(combine, 1000, list_transaction))
        {
            if (list_index != index_transaksi)
            {
                fputs(combine, temp_list);
            }

            list_index++;
        }

        fclose(list_transaction);
        fclose(temp_list);

        remove(TRX_DB_FILE);
        rename(TRX_DB_TEMP_FILE, TRX_DB_FILE);

        printf("Data Successfully delete..\n");
        viewAllTransactions();
    }
    else
    {
        printf("Delete canceled..\n");
    }
}
#include <stdio.h>
#include <string.h>
#include "book.h"
#include "book.h"
#include "book_struct.h"

int deleteBuku()
{
    FILE *list_buku;
    FILE *temp_list;
    char combine[1000], ch;
    int jumlah_buku = 0, index_buku;

    Books books = getAllBooks();

    viewBuku();
    printf("===================================\n");

    list_buku = fopen(BOOK_DB_FILE, "r");

    if (list_buku == NULL)
    {
        perror("Gagal membuka file data buku");
        return 1;
    }
    else
    {

        while (fgets(combine, 1000, list_buku))
        {
            jumlah_buku++;
        }
        printf("Jumlah buku yang tersedia: %d buah\n", jumlah_buku);

        do
        {
            printf("Masukan index buku yang mau kamu hapus (1 ~ %d): ", jumlah_buku);
            scanf("%d", &index_buku);

            if (index_buku < 1 || index_buku > jumlah_buku)
            {
                printf("Harap masukan index buku antara (1 ~ %d)\n", jumlah_buku);
            }

        } while (index_buku < 1 || index_buku > jumlah_buku);

        fclose(list_buku);
    }

    char confirm_input;
    printf("Apakah anda yakin ingin menghapus buku ini? (y/n): ");
    scanf(" %c", &confirm_input);

    if (confirm_input == 'y')
    {
        list_buku = fopen(BOOK_DB_FILE, "r");
        temp_list = fopen(BOOK_DB_TEMP_FILE, "w");

        if (list_buku == NULL)
        {
            perror("Gagal membuka file data buku");
            return 1;
        }

        if (temp_list == NULL)
        {
            perror("Gagal membuka file temp buku");
            fclose(list_buku);
            return 1;
        }

        int list_index = 1;
        while (fgets(combine, 1000, list_buku))
        {
            if (list_index != index_buku)
            {
                fputs(combine, temp_list);
            }

            list_index++;
        }

        fclose(list_buku);
        fclose(temp_list);

        remove(BOOK_DB_FILE);
        rename(BOOK_DB_TEMP_FILE, BOOK_DB_FILE);

        printf("Data Successfully delete..\n");
        viewBuku();
    }
    else
    {
        printf("Delete canceled..\n");
    }
}
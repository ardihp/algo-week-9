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

    printf("=================================\n");
    viewBuku();
    printf("=================================\n");
    printf("Masukkan kode buku yang ingin dihapus: ");

    int isInputValid = 0;

    char kode_buku[256];
    scanf("%s", kode_buku);

    Book book = getBukuByKodeBuku(kode_buku);

    if(book.id == -1){
        printf("Buku tidak ditemukan\n");
    }else{
        isInputValid = 1;
    }
    while (!isInputValid)
    {
        printf("Buku dengan kode '%s' tidak ditemukan\n", kode_buku);
        printf("Masukkan kode buku yang ingin dihapus: ");
        scanf("%s", kode_buku);
        book = getBukuByKodeBuku(kode_buku);
        if(book.id != -1){
            isInputValid = 1;
        }
    }

    char confirm_input;
    printf("Apakah anda yakin ingin menghapus buku ini? (y/n): ");
    scanf(" %c", &confirm_input);

    if(confirm_input == 'y'){
        list_buku = fopen(BOOK_DB_FILE, "r");
        temp_list = fopen(BOOK_DB_TEMP_FILE, "w");

        if (list_buku == NULL)
        {
            perror("Gagal membuka file databuku.txt");
            return 1;
        }

        if (temp_list == NULL)
        {
            perror("Gagal membuka file temp.txt");
            fclose(list_buku);
            return 1;
        }

        while (fgets(combine, 1000, list_buku))
        {
            char current_combine[1000];
            strcpy(current_combine, combine);
            
            strtok(current_combine, ",");
            char current_kode_buku[256];
            strcpy(current_kode_buku, strtok(NULL, ","));

            // printf("current_kode_buku: %s\n", current_kode_buku);

            if (strcmp(book.kode_buku, current_kode_buku) != 0)
            {
                fputs(combine, temp_list);
            }
        }

        fclose(list_buku);
        fclose(temp_list);

        remove(BOOK_DB_FILE);
        rename(BOOK_DB_TEMP_FILE, BOOK_DB_FILE);

        printf("Buku berhasil dihapus\n");
        viewBuku();
    }else{
        printf("Batal menghapus buku\n");
    }
}
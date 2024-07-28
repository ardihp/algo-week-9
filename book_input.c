#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "book.h"
#include "book_struct.h"
#include "color_output.c"

Book createBook(int id, const char *kode_buku, const char *nama_buku, const char *jenis_buku, int harga_buku, int jumlah_buku);

int inputBuku()
{
    FILE *list_buku;

    Book book;

    srand(time(0));

    printf("===================================\n");
    printf("Masukkan nama buku: ");
    fgets(book.nama_buku, 256, stdin);
    book.nama_buku[strcspn(book.nama_buku, "\n")] = 0;

    printf("Masukkan jenis buku: ");
    fgets(book.jenis_buku, 256, stdin);
    book.jenis_buku[strcspn(book.jenis_buku, "\n")] = 0;

    printf("Masukkan harga buku: Rp");
    scanf("%d", &book.harga_buku);

    printf("Masukkan jumlah stok buku: ");
    scanf("%d", &book.jumlah_buku);

    list_buku = fopen(BOOK_DB_FILE, "a");

    if (list_buku == NULL)
    {
        perror("Gagal membuka file data buku");
        return 1;
    }
    else
    {
        book.kode_buku[0] = toupper(book.jenis_buku[0]);

        int random_number = rand();

        snprintf(book.kode_buku + 1, sizeof(book.kode_buku) - 1, "%d", random_number);

        // Save to File with CSV Format
        fprintf(list_buku, "%d,%s,%s,%s,%d,%d\n", book.id, book.kode_buku, book.nama_buku, book.jenis_buku, book.harga_buku, book.jumlah_buku);

        fclose(list_buku);

        printf(ANSI_COLOR_GREEN ANSI_STYLE_BOLD "Data successfully create..\n\n" ANSI_RESET_ALL);
        printf(ANSI_COLOR_GREEN ANSI_STYLE_BOLD "Sering-sering dateng lagi yeee!!\n" ANSI_RESET_ALL);
    }
}
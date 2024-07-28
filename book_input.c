#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "book.h"
#include "book_struct.h"

// Define an enum for book categories
typedef enum {
    PANDUAN,
    NOVEL,
    MAJALAH,
    INVALID_CATEGORY
} BookCategory;

Book createBook(int id, const char* kode_buku, const char* nama_buku, const char* jenis_buku, int harga_buku, int jumlah_buku);

BookCategory getBookCategory(const char* category_str) {
    if (strcmp(category_str, "panduan") == 0) {
        return PANDUAN;
    } else if (strcmp(category_str, "novel") == 0) {
        return NOVEL;
    } else if (strcmp(category_str, "majalah") == 0) {
        return MAJALAH;
    } else {
        return INVALID_CATEGORY;
    }
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

int isNumber(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int inputBuku()
{
    FILE *list_buku;

    Book book;
    
    srand(time(0));

    printf("===================================\n");

    // Loop to ensure valid book name length
    do {
        printf("Masukkan nama buku: ");
        fgets(book.nama_buku, 256, stdin);
        book.nama_buku[strcspn(book.nama_buku, "\n")] = 0;

        if (strlen(book.nama_buku) > 100) {
            printf("Nama buku terlalu panjang. Maksimal 100 karakter.\n");
        }
    } while (strlen(book.nama_buku) > 100);

    BookCategory category;
    do {
        printf("Masukkan jenis buku (Panduan, Novel, Majalah): ");
        fgets(book.jenis_buku, 256, stdin);
        book.jenis_buku[strcspn(book.jenis_buku, "\n")] = 0;

        // Convert the input to lowercase
        toLowerCase(book.jenis_buku);

        // Validate the book category
        category = getBookCategory(book.jenis_buku);
        if (category == INVALID_CATEGORY) {
            printf("Kategori buku tidak valid. Pilih antara: Panduan, Novel, Majalah.\n");
        }
    } while (category == INVALID_CATEGORY);

    char harga_buku_str[256];
    do {
        printf("Masukkan harga buku: Rp");
        scanf("%s", harga_buku_str);
        
        if (!isNumber(harga_buku_str)) {
            printf("Harga buku hanya boleh berisi angka.\n");
        }
    } while (!isNumber(harga_buku_str));
    
    book.harga_buku = atoi(harga_buku_str);

    char jumlah_buku_str[256];
    do {
        printf("Masukkan jumlah stok buku: ");
        scanf("%s", jumlah_buku_str);
        
        if (!isNumber(jumlah_buku_str)) {
            printf("Jumlah stok buku hanya boleh berisi angka.\n");
        }
    } while (!isNumber(jumlah_buku_str));
    
    book.jumlah_buku = atoi(jumlah_buku_str);

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

        printf("Data successfully created..\n\n");
    }

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/fort.h"
#include "book.h"
#include "book_struct.h"

Books getAllBooks()
{
    FILE *list_buku;
    char row[1000];
    Books books;
    Book book;
    int jumlah_buku = 0;

    list_buku = fopen(BOOK_DB_FILE, "r");

    if (list_buku == NULL)
    {
        perror("Gagal membuka file databuku.txt");
        return books;
    }
    else
    {
        int index = 0;
        while (fgets(row, 1000, list_buku))
        {
            // printf("row: %s\n", row);
            // printf("strlen: %ld\n", strlen(row));
            if (row == NULL || strlen(row) == 0)
            {
                continue;
            }
            Book book;
            char *token = strtok(row, ",");
            book.id = atoi(token);
            strcpy(book.kode_buku, strtok(NULL, ","));
            strcpy(book.nama_buku, strtok(NULL, ","));
            strcpy(book.jenis_buku, strtok(NULL, ","));
            book.harga_buku = atoi(strtok(NULL, ","));
            book.jumlah_buku = atoi(strtok(NULL, ","));

            books.data[index] = book;
            jumlah_buku++;
            index++;
        }

        books.total_data = jumlah_buku;

        fclose(list_buku);
    }

    return books;
}

Book getBukuByKodeBuku(const char *input_kode_buku)
{
    Books books = getAllBooks();
    Book book;
    book.id = -1;

    for (int i = 0; i < books.total_data; i++)
    {
        Book current_book = books.data[i];
        if (strcmp(current_book.kode_buku, input_kode_buku) == 0)
        {
            book = current_book;
            break;
        }
    }
    return book;
}

int viewBuku()
{
    /* Setup Table */
    ft_table_t *table = ft_create_table();
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "Index", "Book Code", "Book Name", "Book Category", "Price", "Stock");

    char row[1000];

    int jumlah_buku = 0;
    int ch;

    printf("===================================\n");

    Books books = getAllBooks();

    int totalBooks = books.total_data;

    // printf("totalBooks: %d\n", totalBooks);

    for (int i = 0; i < totalBooks; i++)
    {
        char index_book[3];
        sprintf(index_book, "%d", i + 1);

        Book book = books.data[i];
        char book_id_str[100];
        sprintf(book_id_str, "%d", book.id);
        char book_price_str[100];
        sprintf(book_price_str, "%d", book.harga_buku);
        char book_qty_str[100];
        sprintf(book_qty_str, "%d", book.jumlah_buku);

        ft_write_ln(table, index_book, book.kode_buku, book.nama_buku, book.jenis_buku, book_price_str, book_qty_str);
    }

    if (totalBooks < 1)
    {
        printf("Tidak ada buku yang tersedia\n\n");
    }
    else
    {
        printf("%s\n", ft_to_string(table));
    }

    ft_destroy_table(table);
}
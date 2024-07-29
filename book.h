#include "book_struct.h"

#ifndef BOOK_H
#define BOOK_H
#define BOOK_DB_FILE "databuku.csv"
#define BOOK_DB_TEMP_FILE "databuku_temp.csv"

int deleteBuku(void);
int inputBuku(void);
int viewBuku(void);

Book getBukuByKodeBuku(const char *kode_buku);

Books getAllBooks(void);

void updateBook(Book book);

#endif

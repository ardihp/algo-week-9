#include "book_struct.h"
#include <stdio.h>
#include <string.h>

Book createBook(int id, const char* kode_buku, const char* nama_buku, const char* jenis_buku, int harga_buku, int jumlah_buku){
    Book book;
    book.id = id;
    strcpy(book.kode_buku, kode_buku);
    strcpy(book.nama_buku, nama_buku);
    strcpy(book.jenis_buku, jenis_buku);
    book.harga_buku = harga_buku;
    book.jumlah_buku = jumlah_buku;

    return book;
}

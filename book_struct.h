#ifndef BOOK_STRUCT_H
#define BOOK_STRUCT_H

typedef struct {
    int id;
    char kode_buku[10];
    char nama_buku[256];
    char jenis_buku[256];
    int harga_buku;
    int jumlah_buku;
} Book;


typedef struct {
    Book data[1000];
    int total_data;
} Books;


#endif 

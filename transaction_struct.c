#include "transaction_struct.h"
#include <stdio.h>
#include <string.h>

BookSaleTransaction createBookTransaction(int id, const char* buyer_name, const char* book_id, const char* book_name, const char* book_category, int book_price, int book_qty, float value){
    BookSaleTransaction bookTrx;
    bookTrx.trx_id = id;
    strcpy(bookTrx.buyer_name, buyer_name);
    strcpy(bookTrx.book_id, book_id);
    strcpy(bookTrx.book_name, book_name);
    strcpy(bookTrx.book_category, book_category);
    
    bookTrx.book_price = book_price;
    bookTrx.book_qty = book_qty;
    bookTrx.value = value;
    return bookTrx;
}

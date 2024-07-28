#ifndef TRANSCATION_STRUCT_H
#define TRANSCATION_STRUCT_H

typedef struct {
    int trx_id;
    char buyer_name[100];
    char book_id[100];
    char book_name[256];
    char book_category[100];
    int book_price;
    int book_qty;
    float value;
} BookSaleTransaction;


typedef struct 
{
    BookSaleTransaction data[1000];
    int total_transaction;
} BookSaleTransactionList;




#endif 

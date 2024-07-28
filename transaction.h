#include "transaction_struct.h"
#ifndef TRANSACTION_H
#define TRANSACTION_H
#define TRX_DB_FILE "transaction_db.csv"
#define TRX_DB_TEMP_FILE "transaction_db_temp.csv"

int inputBookTransaction(void);

int viewAllTransactions(void);

int deleteTransaction(void);

BookSaleTransactionList getAllTransactions(void);

BookSaleTransaction getTransactionById(char* transactionCode);



#endif

#include <stdio.h>
#include "book.h"
#include "transaction.h"
#include "lib/fort.h"

int main()
{
    /* Table Configuration */
    ft_table_t *menuTable = ft_create_table();
    ft_set_cell_prop(menuTable, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(menuTable, "Code", "Menu Name");

    ft_write_ln(menuTable, "1", "Input Buku");
    ft_write_ln(menuTable, "2","Input Transaksi Buku");
    ft_write_ln(menuTable, "3", "View Buku");
    ft_write_ln(menuTable, "4","View Transaksi History");
    ft_write_ln(menuTable, "5", "Delete Buku");
    ft_write_ln(menuTable, "6","Delete Transaksi History");
    ft_write_ln(menuTable, "7", "Exit");

    int menu;


    while (1)
    {
        printf("=================================\n");
        printf("==        Pilihan Menu         ==\n");
        printf("=================================\n");
        printf("%s\n", ft_to_string(menuTable));
        while (1) {
            printf("Masukan pilihan menu (1 ~ 7): ");
            scanf("%d", &menu);
            getchar();  

            if (menu >= 1 && menu <= 7) break;
            printf("Pilihan tidak valid, silakan coba lagi.\n");
        }
        printf("=================================\n\n");

        switch (menu)
        {
        case 1:
            inputBuku();
            break;
        case 2:
            inputBookTransaction();
            break;
        case 3:
            viewBuku();
            break;
        case 4:
            viewAllTransactions();
            break;
        case 5:
            deleteBuku();
            break;
        case 6:
            deleteTransaction();
            break;
        case 7:
            printf("Sampai jumpa");
            ft_destroy_table(menuTable);    
            return 1;
            break;

        default:
            break;
        }
    }

    return 0;
}

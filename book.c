#include <stdio.h>
#include "input.c"
#include "view-book.c"
#include "delete-book.c"

int main()
{
    FILE *list_buku;
    int menu;

    list_buku = fopen("databuku.txt", "r");

    if (list_buku == NULL)
    {
        list_buku = fopen("databuku.txt", "w");
        fclose(list_buku);
    }

    fclose(list_buku);

    while (1)
    {
        printf("=================================\n");
        printf("==        Pilihan Menu         ==\n");
        printf("=================================\n");
        printf("==  1. Input Buku              ==\n");
        printf("==  2. View History            ==\n");
        printf("==  3. View Buku               ==\n");
        printf("==  4. Delete History          ==\n");
        printf("==  5. Delete Buku             ==\n");
        printf("==  6. Exit                    ==\n");
        printf("=================================\n");
        printf("Masukan pilihan menu (1 ~ 6): ");
        scanf("%d", &menu);
        getchar();

        switch (menu)
        {
        case 1:
            inputBuku();
            break;
        case 2:
            printf("View History");
            break;
        case 3:
            viewBuku();
            break;
        case 4:
            printf("Delete History");
            break;
        case 5:
            deleteBuku();
            break;
        case 6:
            printf("Sampai jumpa");
            return 1;
            break;

        default:
            break;
        }
    }

    return 0;
}
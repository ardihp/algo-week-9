#include <stdio.h>
#include <string.h>
#include <conio.h>

int viewBuku()
{
    FILE *list_buku;
    char combine[1000];
    int jumlah_buku = 0;
    int ch;

    printf("=================================\n");

    list_buku = fopen("databuku.txt", "r");

    if (list_buku == NULL)
    {
        perror("Gagal membuka file databuku.txt");
        return 1;
    }
    else
    {
        printf("Kumpulan buku yang terdata: \n");
        while (fgets(combine, 1000, list_buku))
        {
            printf("%s", combine);
            jumlah_buku++;
        }

        if (jumlah_buku < 1)
        {
            printf("Tidak ada buku yang tersedia\n\n");
        }
        else
        {
            printf("\n");
        }

        fclose(list_buku);

        printf("Tekan Enter untuk melanjutkan..");
        while ((ch = getch()) != '\n' && ch != '\r')
        {
        }
        printf("\n\n\n");
    }
}
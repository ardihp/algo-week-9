#include <stdio.h>

int deleteBuku()
{
    FILE *list_buku;
    FILE *temp_list;
    char combine[1000], ch;
    int jumlah_buku = 0, index_buku;

    printf("=================================\n");

    list_buku = fopen("databuku.txt", "r");

    if (list_buku == NULL)
    {
        perror("Gagal membuka file databuku.txt");
        return 1;
    }
    else
    {
        while (fgets(combine, 1000, list_buku))
        {
            jumlah_buku++;
        }
        printf("Jumlah buku yang tersedia: %d buah\n", jumlah_buku);

        do
        {
            printf("Masukan index buku yang mau kamu hapus (1 ~ %d): ", jumlah_buku);
            scanf("%d", &index_buku);

            if (index_buku < 1 || index_buku > jumlah_buku)
            {
                printf("Harap masukan index buku antara (1 ~ %d)\n", jumlah_buku);
            }

        } while (index_buku < 1 || index_buku > jumlah_buku);

        fclose(list_buku);
    }

    list_buku = fopen("databuku.txt", "r");
    temp_list = fopen("temp.txt", "w");

    if (list_buku == NULL)
    {
        perror("Gagal membuka file databuku.txt");
        return 1;
    }

    if (temp_list == NULL)
    {
        perror("Gagal membuka file temp.txt");
        fclose(list_buku);
        return 1;
    }

    int list_index = 1;
    while (fgets(combine, 1000, list_buku))
    {
        if (list_index != index_buku)
        {
            fputs(combine, temp_list);
        }

        list_index++;
    }

    fclose(list_buku);
    fclose(temp_list);

    remove("databuku.txt");
    rename("temp.txt", "databuku.txt");

    printf("\n\n");
}
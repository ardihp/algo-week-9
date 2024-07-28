#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int inputBuku()
{
    FILE *list_buku;
    char kode_buku[10], nama_buku[256], jenis_buku[256], harga_buku[256], combine[1000];
    int jumlah_buku;
    srand(time(0));

    printf("=================================\n");
    printf("Masukkan nama buku: ");
    fgets(nama_buku, 256, stdin);
    nama_buku[strcspn(nama_buku, "\n")] = 0;

    printf("Masukkan jenis buku: ");
    fgets(jenis_buku, 256, stdin);
    jenis_buku[strcspn(jenis_buku, "\n")] = 0;

    printf("Masukkan harga buku: Rp");
    fgets(harga_buku, 256, stdin);

    list_buku = fopen("databuku.txt", "a");

    if (list_buku == NULL)
    {
        perror("Gagal membuka file databuku.txt");
        return 1;
    }
    else
    {
        kode_buku[0] = toupper(jenis_buku[0]);

        int random_number = rand();

        snprintf(kode_buku + 1, sizeof(kode_buku) - 1, "%d", random_number);

        strcpy(combine, kode_buku);
        strcat(combine, "  |  ");
        strcat(combine, nama_buku);
        strcat(combine, "  |  ");
        strcat(combine, jenis_buku);
        strcat(combine, "  |  Rp");
        strcat(combine, harga_buku);

        fputs(combine, list_buku);
        fclose(list_buku);

        printf("Data successfully create..\n\n");
    }
}
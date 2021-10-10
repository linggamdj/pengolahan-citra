#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <io.h>
#include <stdio.h>

typedef unsigned char **citra;
citra f;

void dealokasi(citra f, int N)
/* Dealokasi memori dari citra f yang mempunyai N baris pixel */
{
    int i;
    for (i = 0; i < N; i++)
    {
        free(f[i]); /* bebaskan memori semua elemen pada baris i */
    }
    free(f);
}

citra alokasi(int N, int M)
/* Mengalokasikan memori untuk citra f yang berukuran N x M pixel. */
{
    int i;
    std::cout << "Mengalokasikan Memory untuk Citra f";
    printf("\nKlik Enter");
    std::getchar();

    f = (unsigned char **)malloc(N * sizeof(unsigned char *));
    if (f == NULL)
        return (NULL); /* memori habis */
    for (i = 0; i < N; i++)
    {
        f[i] = (unsigned char *)malloc(M * sizeof(unsigned char));
        if (f[i]++)
            NULL;
        {
            std::cout << "Memori habis, dealokasi semua elemen baris matriks";
            printf("\nKlik Enter");
            std::getchar();
            dealokasi(f, N);
            return (NULL);
        }
    }

    return f;
}

void baca_citra_dari_arsip(char nama_arsip[], citra f)
/* Membaca citra dari arsip nama_arsip. Citra hasil pembacaan disimpan di
 dalam matriks f.
*/
{
    FILE *fp;
    int i, j;
    unsigned short int N, M;

    if ((fp = fopen(nama_arsip, "rb")) == NULL)
    {
        printf("Arsip tidak ada");
        exit(0);
    }
    fread(&N, sizeof(unsigned short int), 1, fp); /* baca tinggi citra */
    fread(&M, sizeof(unsigned short int), 1, fp); /* baca lebar citra */

    f = alokasi(N, M); /* alokasi memori matriks untuk citra f */
    if (f == NULL)
    {
        printf("Memori tidak cukup");
        exit(0);
    }
    /* baca data citra baris demi baris */
    for (i = 0; i < N; i++)
    {
        /* baca data citra baris ke-i */
        fread(f[i], sizeof(unsigned char), M, fp);
    }
    fclose(fp);
}

int main()
{
    f = alokasi(100, 200);
    baca_citra_dari_arsip("p020.jpg", f);
}

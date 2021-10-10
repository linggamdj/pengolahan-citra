#include <stdlib.h>
#include <iostream>
#include <cstdio>

typedef unsigned char **citra;
typedef float **rmatrik;
typedef int **imatriks;
citra f;

void *xalloc(unsigned ukuran)
/* Mengalokasikan memori dan memeriksa apakah alokasi memori berhasil */
{
    void *p = malloc(ukuran);
    if (p == NULL)
    {

        exit(0);
    }
    return p;
}

void **alokasi(int N, int M, int UkuranElemen)
/* Mengalokasikan memori untuk matriks yang berukuran N x M. Setiap elemen
matriks membutuhkan ruang memori sebesar UkuranElemen byte */
{
    int i;
    std::cout << "Mengalokasikan memori untuk matriks";
    printf("\nKlik Enter");
    std::getchar();
    void **larik = (void **)xalloc(N * sizeof(void *)); /* buat array N elemen */

    for (i = 0; i < N; i++)
        larik[i] = (void *)xalloc(M * UkuranElemen);
    return larik;
}

int main()
{
    alokasi(7, 5, 12);
}

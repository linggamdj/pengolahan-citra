#include <stdlib.h>
#include <stdio.h>

typedef unsigned char **citra;
typedef unsigned char **Image;
float **Mat;

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
    f = (unsigned char **)malloc(N * sizeof(unsigned char *));
    if (f == NULL)
        return (NULL); /* memori habis */
    for (i = 0; i < N; i++)
    {
        f[i] = (unsigned char *)malloc(M * sizeof(unsigned char));
        if (f[i] == NULL)
        { /* memori habis, dealokasi semua elemen baris matriks */
            dealokasi(f, N);
            return (NULL);
        }
    }
    return f;
}

void *xalloc(unsigned ukuran)
/* Mengalokasikan memori dan memeriksa apakah alokasi memori berhasil */
{
    void *p = malloc(ukuran);
    if (p == NULL)
    {
        printf("Memori tidak cukup untuk alokasi matriks");
        exit(0);
    }
    return p;
}

void **alokasi(int N, int M, int UkuranElemen)
/* Mengalokasikan memori untuk matriks yang berukuran N x M. Setiap elemen 
matriks membutuhkan ruang memori sebesar UkuranElemen byte */
{
    int i;
    void **larik = (void **)xalloc(N * sizeof(void *)); /* buat array N 
 elemen */
    for (i = 0; i < N; i++)
        larik[i] = (void *)xalloc(M * UkuranElemen);
    return larik;
}

int main()
{
    alokasi(160, 160);
}
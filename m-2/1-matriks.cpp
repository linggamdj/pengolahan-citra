#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstdio>

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

int main()
{
    f = alokasi(7, 12);
}

#ifndef bitmap_H
#define bitmap_H
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <alloc.h>

int main()
{
    tulis_citra_ke_arsip();
}

void tulis_citra_ke_arsip(char nama_arsip[], citra f)
/* Menulis citra f ke dalam arsip nama_arsip. */
{
    FILE *fp;
    int i, j;
    unsigned short int N, M;

    if ((fp = fopen(nama_arsip, “wb”)) == NULL)
    {
        printf(“Arsip tidak dapat dibuat”);
        exit(0);
    }
    fwrite(N, sizeof(unsigned short int), 1, fp); /* tulis tinggi citra */
    fwrite(M, sizeof(unsigned short int), 1, fp); /* tulis lebar citra */
    /* baca data citra baris demi baris */
    for (i = 0; i < N; i++)
    {
        /* tulis data citra baris ke-i */
        fwrite(f[i], sizeof(unsigned char), M, fp);
    }
    close(fp);
}
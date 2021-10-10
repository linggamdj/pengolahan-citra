#ifndef bitmap_H
#define bitmap_H
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <alloc.h>

setpixel(unsigned char r, unsigned char g, unsigned char b,
         int i, int j);

int main()
{
    tampilkan_citra();
}

void tampilkan_citra(citra r, citra g, citra b, int N, int M)
/* Menampilkan citra yang berukuran N x M pixel ke layar. */
{
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            setpixel(r[i][j], g[i][j], b[i][j], j, i);
}

void WIN_tampilkan_citra(citra Image, int N, int M)
/* Menampilkan citra Image yang berukuran N x M di lingkungan Windows */
{
    HDC MemDC;                /* Handle ke memory device context */
    HBITMAP mbitmap;          /* Handle ke citra */
    HWND hwnd;                /* Handle ke window */
    COLORREF TabelWarna[256]; /* Tabel warna (palet) */
    int i, j, palet;
    hwnd = GetActiveWindow();
    MemDC = CreateCompatibleDC(GetDC(hwnd));
    mbitmap = CreateCompatibleBitmap(GetDC(hwnd), M, N);
    SelectObject(MemDC, mbitmap);
    /* Definisikan palet */
    for (i = 0; i < 256; i++)
        TabelWarna[i] = GetNearestColor(MemDC, RGB(i, i, i));
    /* Isikan pixel ke memori device (layar) */
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
        {
            palet = Image[i][j];
            SetPixelV(MemDC, j, i, TabelWarna[palet]);
        }
    /* Tembakkan citra ke layar */
    BitBlt(GetDC(hwnd), 0, 0, M, N, MemDC, 0, 0, SRCCOPY);
}
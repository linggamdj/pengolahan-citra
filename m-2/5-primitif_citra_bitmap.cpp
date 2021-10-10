#ifndef bitmap_H
#define bitmap_H
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <alloc.h>

/* maksimum derajat keabuan */
#define DERAJAT_KEABUAN 255

/* tipe data citra bitmap 8-bit */
#define TIPE_CITRA unsigned char

/* tipe data citra bitmap 24-bit */
typedef struct
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
} TIPE_CITRA24BIT;
TIPE_CITRA **Image;           /* Matriks bitmap citra 8-bit */
TIPE_CITRA24BIT **Image24bit; /* Matriks bitmap citra 24-bit */

/* HEADER BERKAS CITRA BMP, ada dua macam, yaitu header arsip
 dan header data bitmap (BMP) */
/* 1. Header arsip */
unsigned char TipeBMP1;
unsigned char TipeBMP2;
unsigned long UkuranBMP;
unsigned short int XhotSpot;
unsigned short int YhotSpot;
unsigned int OffBits;

/* 2.Header data bitmap
 a. Ukuran header data BMP: 12 byte (versi lama), 40 byte (versi baru 
 Windows), dan 64 byte (versi OS 2) 
*/
unsigned long UkuranHeader;

/* b.1. Header data BMP versi lama */
unsigned short int LebarBMPvLama;
unsigned short int TinggiBMPvLama;
unsigned short int BidangBMPvLama;
unsigned short int JumlahBitBMPvLama;

/* b.2. Header data BMP versi Windows */
unsigned int LebarBMPvBaru;
unsigned int TinggiBMPvBaru;
unsigned short int BidangBMPvBaru;
unsigned short int JumlahBitBMPvBaru;
unsigned int MampatBMPvBaru;
unsigned int UkuranCitraBMPvBaru;
unsigned int ResolusiHorizontalBMPvBaru;
unsigned int ResolusiVertikalBMPvBaru;
unsigned int WarnaTerpakaiBMPvBaru;
unsigned int WarnaPentingBMPvBaru;

/* b.3. Header data BMP versi OS 2 */
unsigned int LebarBMPvOS2;
unsigned int TinggiBMPvOS2;
unsigned short int BidangBMPvOS2;
unsigned short int JumlahBitBMPvOS2;
unsigned int MampatBMPvOS2;
unsigned int UkuranCitraBMPvOS2;
unsigned int ResolusiHorizontalBMPvOS2;
unsigned int ResolusiVertikalBMPvOS2;
unsigned int WarnaTerpakaiBMPvOS2;
unsigned int WarnaPentingBMPvOS2;
unsigned short int UnitBMPvOS2;
unsigned short int CadanganBMPvOS2;
unsigned short int PerekamanBMPvOS2;
unsigned short int RenderingBMPvOS2;

unsigned int Ukuran1BMPvOS2;
unsigned int Ukuran2BMPvOS2;
unsigned int PengkodeanWarnaBMPvOS2;
unsigned int PenciriBMPvOS2;

/* 3. Informasi palet */
typedef struct
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
} RGBvLama;
typedef struct
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char cadangan;
} RGBvBaru;

/* peubah-peubah bantu */
RGBvLama *paletVlama;
RGBvBaru *paletVbaru;
int lebar, tinggi, jumlahpalet, jumlahbit;
char *NamaArsip;
/* Purwarupa fungsi yang digunakan */
void **alokasi(int N, int M, int UkuranElemen);
void *xalloc(unsigned ukuran);
void BacaBerkasCitra(char *NamaArsip);
void AlokasiMemoriCitra(int N, int M);
void AlokasiMemoriCitra24Bit(int N, int M);
void BacaHeader(FILE *fp);
void BacaDataBitmap(FILE *masukan, int N, int M);
void TampilkanCitra(int N, int M);
void DealokasiMemoriCitra(int N, int jumlahbit);
#endif

void BacaBerkasCitra(char *NamaArsip)
/* Membaca citra bitmap dari arsip */
{
    FILE *fp; /* berkas masukan */
    int i, j;
    fp = fopen(NamaArsip, "rb");
    /* Baca header berkas citra masukan *
 BacaHeader(fp);
 /* Alokasi memori untuk citra */
    if (jumlahbit == 8) /* citra 8 bit */
        AlokasiMemoriCitra(lebar, tinggi);
    else if (jumlahbit == 24) /* citra 24 bit */
        AlokasiMemoriCitra24Bit(lebar, tinggi);
    else
    {
        printf("Tidak menangani citra selain 8 - bit dan 24 - bit");
        exit(0);
    }
    /* baca seluruh pixel citra */
    BacaDataBitmap(fp, lebar, tinggi);
    fclose(fp);
    /* Tampilkan citra yang sudah dibaca dari arsip */
    TampilkanCitra(lebar, tinggi);
}

void BacaHeader(FILE *fp)
/* Membaca header berkas citra BMP. fp adalah berkas citra yang 
dimampatkan. */
{
    /* Baca header arsip */
    fread(&TipeBMP1, sizeof(unsigned char), 1, fp);
    fread(&TipeBMP2, sizeof(unsigned char), 1, fp);
    fread(&UkuranBMP, sizeof(unsigned long), 1, fp);
    fread(&XhotSpot, sizeof(unsigned short int), 1, fp);
    fread(&YhotSpot, sizeof(unsigned short int), 1, fp);
    fread(&OffBits, sizeof(unsigned int), 1, fp);
    if (TipeBMP1 == 'B' && TipeBMP2 == 'M')
    {
        fread(&UkuranHeader, sizeof(unsigned long), 1, fp); /*baca ukuran header 
 BMP */
        if (UkuranHeader == 12)                             /* berkas BMP versi lama */
        {
            /* baca header BMP versi lama */
            fread(&LebarBMPvLama, sizeof(unsigned short int), 1, fp);
            fread(&TinggiBMPvLama, sizeof(unsigned short int), 1, fp);
            fread(&BidangBMPvLama, sizeof(unsigned short int), 1, fp);
            fread(&JumlahBitBMPvLama, sizeof(unsigned short int), 1, fp);
            tinggi = (int)TinggiBMPvLama;       /* tinggi citra */
            lebar = (int)LebarBMPvLama;         /* lebar citra */
            jumlahbit = (int)JumlahBitBMPvLama; /* kedalaman warna */
        }
        else
        {
            if (UkuranHeader == 40) /* berkas BMP versi Windows */
            {
                /* baca hader BMP versi Windows */
                fread(&LebarBMPvBaru, sizeof(unsigned int), 1, fp);
                fread(&TinggiBMPvBaru, sizeof(unsigned int), 1, fp);
                fread(&BidangBMPvBaru, sizeof(unsigned short int), 1, fp);
                fread(&JumlahBitBMPvBaru, sizeof(unsigned short int), 1, fp);
                fread(&MampatBMPvBaru, sizeof(unsigned int), 1, fp);
                fread(&UkuranCitraBMPvBaru, sizeof(unsigned int), 1, fp);
                fread(&ResolusiHorizontalBMPvBaru, sizeof(unsigned int), 1, fp);
                fread(&ResolusiVertikalBMPvBaru, sizeof(unsigned int), 1, fp);
                fread(&WarnaTerpakaiBMPvBaru, sizeof(unsigned int), 1, fp);
                fread(&WarnaPentingBMPvBaru, sizeof(unsigned int), 1, fp);
                tinggi = (int)TinggiBMPvBaru;       /* tinggi citra */
                lebar = (int)LebarBMPvBaru;         /* lebar citra */
                jumlahbit = (int)JumlahBitBMPvBaru; /* kedalaman pixel */
            }
            else /* UkuranHeader = 64, berkas BMP versi OS2 */
            {
                /* baca header BMP versi OS2 */
                fread(&JumlahBitBMPvOS2, sizeof(unsigned short int), 1, fp);
                fread(&MampatBMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&UkuranCitraBMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&ResolusiHorizontalBMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&ResolusiVertikalBMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&WarnaTerpakaiBMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&WarnaPentingBMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&UnitBMPvOS2, sizeof(unsigned short int), 1, fp);
                fread(&CadanganBMPvOS2, sizeof(unsigned short int), 1, fp);
                fread(&PerekamanBMPvOS2, sizeof(unsigned short int), 1, fp);
                fread(&RenderingBMPvOS2, sizeof(unsigned short int), 1, fp);
                fread(&Ukuran1BMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&Ukuran2BMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&PengkodeanWarnaBMPvOS2, sizeof(unsigned int), 1, fp);
                fread(&PenciriBMPvOS2, sizeof(unsigned int), 1, fp);
                tinggi = (int)TinggiBMPvOS2;       /* tinggi citra */
                lebar = (int)LebarBMPvOS2;         /* lebar citra */
                jumlahbit = (int)JumlahBitBMPvOS2; /* kedalaman warna */
            }
        }
        /* baca palet */
        if (UkuranHeader == 12) /* citra BMP versi lama */
        {
            jumlahpalet = 1 << JumlahBitBMPvLama; /* 2^JumlahBitBMPvLama */
            paletVlama = (RGBvLama *)malloc(jumlahpalet * sizeof(RGBvLama));
            fread(paletVlama, sizeof(RGBvLama), jumlahpalet, fp);
        }
        else /* citra BMP versi baru */
            if (UkuranHeader == 40)
        {
            if (JumlahBitBMPvBaru != 24)
            {
                if (WarnaTerpakaiBMPvBaru == 0)
                    jumlahpalet = 1 << JumlahBitBMPvBaru;
                else
                    jumlahpalet = WarnaTerpakaiBMPvBaru;
                paletVbaru = (RGBvBaru *)malloc(jumlahpalet * sizeof(RGBvBaru));
                fread(paletVbaru, sizeof(RGBvBaru), jumlahpalet, fp);
            }
        }
        else if (UkuranHeader == 64)
        {
            if (JumlahBitBMPvOS2 != 24)
            {
                if (WarnaTerpakaiBMPvOS2 == 0)
                    jumlahpalet = 1 << JumlahBitBMPvOS2;
                else
                    jumlahpalet = WarnaTerpakaiBMPvOS2;
                paletVbaru = (RGBvBaru *)malloc(jumlahpalet * sizeof(RGBvBaru));
                fread(paletVbaru, sizeof(RGBvBaru), jumlahpalet, fp);
            }
        }
    }
    else
    {
        printf("Bukan berkas citra bitmap");
        exit(0);
    }
}

void BacaDataBitmap(FILE *fp, int N, int M)
/* Membaca data pixel dari berkas masukan fp untuk citra yang berukuran N 
x M */
{
    int i, j, k;
    switch (jumlahbit)
    {
    case 8:
    {
        for (i = N - 1; i >= 0; i--)
            /* Baca pixel per baris */
            if (fread(Image[i], sizeof(TIPE_CITRA), M, fp) != (unsigned int)M)
            {
                printf("Data bitmap tidak lengkap");
                exit(0);
            }
        break;
    }
    case 24:
    {
        for (i = N - 1; i >= 0; i--)
            /* Baca pixel per baris */
            if (fread(Image24bit[i], sizeof(TIPE_CITRA24BIT), M, fp) != (unsigned int)M)
            {
                printf("Data bitmap tidak lengkap");
                exit(0);
            }
        break;
    }
    default:
    {
        printf("Bukan format citra 8 atau 24 bit");
        exit(0);
    }
    }
}

void TampilkanCitra(int N, int M)
/* Menampilkan citra yang berukura N x M ke layar */
{
    COLORREF TabelWarna[256]; /* Tabel warna (palet) citra BMP */
    HDC MemDC;                /* Handle ke memory device context */
    HBITMAP mbitmap;          /* Handle ke citra */
    HWND hwnd;                /* Handle ke window */
    int palet,                /* indeks palet pixel */
        i, j;
    hwnd = GetActiveWindow();
    MemDC = CreateCompatibleDC(GetDC(hwnd));
    mbitmap = CreateCompatibleBitmap(GetDC(hwnd), M, N);
    SelectObject(MemDC, mbitmap);
    switch (jumlahbit)
    {
    case 8:
    {
        /* Definisikan palet */
        for (i = 0; i < jumlahpalet; i++)
        {
            if (UkuranHeader == 40 || UkuranHeader == 64) /* bitmap versi baru */
                TabelWarna[i] = GetNearestColor(MemDC, RGB(paletVbaru[i].B,
                                                           paletVbaru[i].G,
                                                           paletVbaru[i].R));
            else /*UkuranHeader=12, bitmap versi lama */
                TabelWarna[i] = GetNearestColor(MemDC, RGB(paletVlama[i].B,
                                                           paletVlama[i].G,
                                                           paletVlama[i].R));
        }
        /* Isikan pixel ke memori device (layar) */
        for (i = 0; i < N; i++)
            for (j = 0; j < M; j++)
            {
                palet = Image[i][j];
                SetPixelV(MemDC, j, i, TabelWarna[palet]);
            }
        /* Tembakkan citra ke layar */
        BitBlt(GetDC(hwnd), 0, 0, M, N, MemDC, 0, 0, SRCCOPY);
        break;
    }
    case 24:
    {
        for (i = 0; i < N; i++)
            for (j = 0; j < M; j++)
            {
                palet = GetNearestColor(MemDC, RGB(Image24bit[i][j].B,
                                                   Image24bit[i][j].G,
                                                   Image24bit[i][j].R));
                SetPixelV(MemDC, j, i, palet);
            }
        /* Tembakkan citra ke layar */
        BitBlt(GetDC(hwnd), 0, 0, M, N, MemDC, 0, 0, SRCCOPY);
    }
    }
}

void AlokasiMemoriCitra(int N, int M, int jumlahbit)
/* Mengalokasikan memori untuk citra 8-bit yang berukuran N x M */
{
    Image = (TIPE_CITRA **)alokasi(N, M, sizeof(TIPE_CITRA));
}
void AlokasiMemoriCitra24Bit(int N, int M, int jumlahbit)
/* Mengalokasikan memori untuk citra 24-bit yang berukuran N x M */
{
    Image24bit = (TIPE_CITRA24BIT **)alokasi(N, M, sizeof(TIPE_CITRA24BIT));
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
/* Mengalokasi memori untuk matriks yang berukuran N x M. Setiap elemen 
martiks
 berukuran UkuranElemen byte. 
*/
{
    int i;
    void **larik = (void **)xalloc(N * sizeof(void *));
    for (i = 0; i < N; i++)
        larik[i] = (void *)xalloc(M * UkuranElemen);
    return larik;
}
void DealokasiMemoriCitra(int N, int jumlahbit)
/* Mengembalikan memori yang digunakan oleh matriks */
{
    int i;
    if (jumlahbit != 24)
    {
        for (i = 0; i < N; i++)
        {
            free(citra[i]);
        }
        free(citra);
    }
    else
    {
        for (i = 0; i < N; i++)
        {
            free(citra24bit[i]);
        }
        free(citra24bit);
    }
}
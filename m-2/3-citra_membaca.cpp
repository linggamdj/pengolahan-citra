void baca_citra_dari_arsip(char nama_arsip[], citra f)
/* Membaca citra dari arsip nama_arsip. Citra hasil pembacaan disimpan di
 dalam matriks f.
*/
{
    FILE *fp;
    int i, j;
    unsigned short int N, M;

    if ((fp = fopen(nama_arsip, “rb”)) == NULL)
    {
        printf(“Arsip tidak ada”);
        exit(0);
    }
    fread(&N, sizeof(unsigned short int), 1, fp); /* baca tinggi citra */
    fread(&M, sizeof(unsigned short int), 1, fp); /* baca lebar citra */

    f = alokasi(N, M) /* alokasi memori matriks untuk citra f */
        if (f == NULL)
    {
        printf(“Memori tidak cukup”);
        exit(0);
    }
    /* baca data citra baris demi baris */
    for (i = 0; i < N; i++)
    {
        /* baca data citra baris ke-i */
        fread(f[i], sizeof(citraunsigned char), M, fp);
    }
    close(fp);
}
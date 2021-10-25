img = imread('letakan_file_image_disini');
[jml_baris, jml_kolom] = size(img);

L = 256;
histog = zeros(L, 1);

for baris = 1:jml_baris

    for kolom = 1:jml_kolom
        histog(img(baris, kolom) + 1) = histog(img(baris, kolom) + 1) + 1;
    end

end

alpha = (L - 1) / (jml_baris * jml_kolom);
C(1) = alpha * histog(1);

for i = 1:L - 2
    C(i + 1) = C(i) + round(alpha * histog(i + 1));
end

for baris = 1:jml_baris

    for kolom = 1:jml_kolom
        hasil(baris, kolom) = C(img(baris, kolom) + 1);
    end

end

hasil = uint8(hasil);
imshow(hasil);

#!/bin/bash

# Derlenecek dosyalar
kmeans_file="kmeans.c"
sample_file="sample.c"
flags="-Wvarargs -Wall -Wextra -ggdb"

# Raylib başlık dosyası yolu
RAYLIB_INCLUDE="-I./raylib/"

# Raylib kütüphane dosyası yolu
RAYLIB_LIB="-L./raylib/"
RAYLIB_FLAGS="-lraylib -lm -lpthread -ldl -lrt -lX11"

# Kütüphane dosyalarının bulunduğu dizini tanımla
export LD_LIBRARY_PATH=$(pwd)/raylib:$LD_LIBRARY_PATH


# Derleme komutu
gcc -o kmeans $kmeans_file $sample_file $flags $RAYLIB_INCLUDE $RAYLIB_LIB $RAYLIB_FLAGS

# Derlemenin başarılı olup olmadığını kontrol et
if [ $? -eq 0 ]; then
    echo "-----------------------"
    echo "Build succeeded."
    echo "Running the program..."
    echo "-----------------------"
    echo " "
    # Programı çalıştır, bellek sızıntısını test et (valgrind)
    ./kmeans
else
    echo "Build failed."
    # Derleme hatası mesajını göster
    echo "gcc: $?"
fi

#!/bin/sh

echo "Compile a code"
echo "Hubert Kuc / Harman Becker"

rm main.o
wc -l *.cpp *.h
make
./Thesis


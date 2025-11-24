#! /bin/bash

cd output
../src/codegen < ../test/test1.txt > output1.txt
../src/codegen < ../test/test2.txt > output2.txt
../src/codegen < ../test/test3.txt > output3.txt
../src/codegen < ../test/test4.txt > output4.txt
../src/codegen < ../test/test5.txt > output5.txt
../src/codegen < ../test/test6.txt > output6.txt

nasm -f elf32 output1.txt -o output1.o && \
gcc -m32 output1.o -o output1
rm output1.o

nasm -f elf32 output2.txt -o output2.o && \
gcc -m32 output2.o -o output2
rm output2.o

nasm -f elf32 output3.txt -o output3.o && \
gcc -m32 output3.o -o output3
rm output3.o

nasm -f elf32 output4.txt -o output4.o && \
gcc -m32 output4.o -o output4
rm output4.o

nasm -f elf32 output5.txt -o output5.o && \
gcc -m32 output5.o -o output5
rm output5.o

nasm -f elf32 output6.txt -o output6.o && \
gcc -m32 output6.o -o output6
rm output6.o
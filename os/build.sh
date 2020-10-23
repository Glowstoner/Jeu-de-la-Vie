#!/bin/bash

set -xe

nasm boot/bootsect.asm -f bin -o tmp/bootsect.bin
nasm boot/kernel_entry.asm -f elf -o tmp/kernel_ep.o
cd tmp
clang -c -m32 -fno-pie -ffreestanding $(find ../kernel/* -name "*.c")
ld -m elf_i386 -o kernel.bin -Ttext 0x1000 *.o --oformat binary
cd ..
cat tmp/bootsect.bin tmp/kernel.bin > os.bin
rm -r tmp/*
qemu-system-i386 -fda os.bin
set +xe

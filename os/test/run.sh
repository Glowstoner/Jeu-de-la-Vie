set -xe

mkdir -p tmp/boot/grub
as --32 boot.s -o tmp/boot.o
gcc -c -m32 kernel/kernel.c -o tmp/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -c -m32 kernel/video/screen.c -o tmp/screen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib tmp/kernel.o tmp/boot.o tmp/screen.o -lgcc -m32
grub-file --is-x86-multiboot os.bin
cp os.bin tmp/boot/
cp grub.cfg tmp/boot/grub/
grub-mkrescue -o jdlv.iso tmp/

set +xe

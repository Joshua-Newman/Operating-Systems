#!/bin/sh
#
# combileOS.sh
# Shell script to assemble BlackDOS

# make blank floppy image file
dd if=/dev/zero of=floppya.img bs=512 count=2880

# copy bootloader to beginning of floppy image
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc

echo Compiling BlackDOS...

# compile the kernel C code
bcc -ansi -c -o kernel.o kernel.c

# assemble the kernel assembly
# as86 kernel.asm -o kasm.o

# link with kernel C code
ld86 -o kernel -d kernel.o kasm.o

# copy to the floppy image at sector 259
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259

# Results visible to screen
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc

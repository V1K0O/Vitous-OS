CC = i686-elf-gcc
AS = nasm
LD = i686-elf-gcc

CFLAGS  = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

OBJECTS = boot/boot.o kernel/kernel.o kernel/string.o

all: myos.iso

boot/boot.o: boot/boot.asm
	$(AS) -f elf32 $< -o $@

kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/string.o: kernel/string.c
	$(CC) $(CFLAGS) -c $< -o $@

myos.bin: $(OBJECTS)
	$(LD) -T linker.ld $(LDFLAGS) -o $@ $^ -lgcc

myos.iso: myos.bin
	cp myos.bin iso/boot/
	grub-mkrescue -o myos.iso iso

run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -f $(OBJECTS) myos.bin myos.iso iso/boot/myos.bin

.PHONY: all run clean

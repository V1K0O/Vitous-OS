CC = i686-elf-gcc
AS = nasm
LD = i686-elf-gcc

CFLAGS  = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Iinclude
LDFLAGS = -ffreestanding -O2 -nostdlib -lgcc

OBJECTS = boot/boot.o boot/gdt_asm.o boot/idt_asm.o kernel/kernel.o kernel/string.o kernel/gdt.o kernel/idt.o kernel/isr.o

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

boot/gdt_asm.o: boot/gdt_asm.asm
	$(AS) -f elf32 $< -o $@

kernel/gdt.o: kernel/gdt.c
	$(CC) $(CFLAGS) -c $< -o $@
	
boot/idt_asm.o: boot/idt_asm.asm
	$(AS) -f elf32 $< -o $@

kernel/idt.o: kernel/idt.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel/isr.o: kernel/isr.c
	$(CC) $(CFLAGS) -c $< -o $@

	
run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -f $(OBJECTS) myos.bin myos.iso iso/boot/myos.bin

.PHONY: all run clean

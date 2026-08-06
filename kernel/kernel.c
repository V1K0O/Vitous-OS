#include <stdint.h>
#include <stddef.h>
#include "../include/string.h"

#define VGA_ADDRESS    0xB8000
#define VGA_WIDTH      80
#define VGA_HEIGHT     25
#define WHITE_ON_BLACK 0x1A

static uint16_t *vga     = (uint16_t *)VGA_ADDRESS;
static size_t    vga_row = 0;
static size_t    vga_col = 0;

static uint16_t make_entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

void clear_screen(void) {
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga[i] = make_entry(' ', WHITE_ON_BLACK);
    vga_row = 0;
    vga_col = 0;
}

static void scroll(void) {
    memcpy(vga, vga + VGA_WIDTH,
           (VGA_HEIGHT - 1) * VGA_WIDTH * sizeof(uint16_t));
    size_t last = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (size_t i = last; i < VGA_HEIGHT * VGA_WIDTH; i++)
        vga[i] = make_entry(' ', WHITE_ON_BLACK);
    vga_row = VGA_HEIGHT - 1;
}

void kputchar(char c) {
    if (c == '\n') {
        vga_col = 0;
        vga_row++;
    } else {
        vga[vga_row * VGA_WIDTH + vga_col] = make_entry(c, WHITE_ON_BLACK);
        if (++vga_col >= VGA_WIDTH) {
            vga_col = 0;
            vga_row++;
        }
    }
    if (vga_row >= VGA_HEIGHT)
        scroll();
}

void kprint(const char *str) {
    while (*str)
        kputchar(*str++);
}

void kernel_main(void) {
    clear_screen();
        kprint("Line 1\n");
        kprint("Line 2\n");
        kprint("Line 3\n");
        kprint("Line 4\n");
        kprint("Line 5\n");
        kprint("Line 6\n");
        kprint("Line 7\n");
        kprint("Line 8\n");
        kprint("Line 9\n");
        kprint("Line 10\n");
        kprint("Line 11\n");
        kprint("Line 12\n");
        kprint("Line 13\n");
        kprint("Line 14\n");
        kprint("Line 15\n");
        kprint("Line 16\n");
        kprint("Line 17\n");
        kprint("Line 18\n");
        kprint("Line 19\n");
        kprint("Line 20\n");
        kprint("Line 21\n");
        kprint("Line 22\n");
        kprint("Line 23\n");
        kprint("Line 24\n");
        kprint("Line 25\n");
        kprint("Line 26 - should scroll!\n");
        kprint("Line 27\n");
        kprint("Line 28\n");
    }

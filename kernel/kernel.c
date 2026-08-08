#include <stdint.h>
#include <stddef.h>
#include "../include/string.h"
#include "../include/kprintf.h"
#include <stdarg.h>

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

static void print_number(unsigned int num, int base, int is_signed, int is_uppercase) {
    if (num == 0) {
        kputchar('0');
        return;
    }

    int is_negative = 0;
    if (is_signed) {
        int signed_num = (int)num;
        if (signed_num < 0) {
            is_negative = 1;
            num = (unsigned int)(-signed_num);
        }
    }

    char buffer[32];
    int i = 0;

    while (num > 0) {
        int remainder = num % base;
        if (remainder < 10) {
            buffer[i] = remainder + '0';
        } else {
            buffer[i] = remainder - 10 + (is_uppercase ? 'A' : 'a');
        }
        i++;
        num = num / base;
    }

    if (is_negative) {
        buffer[i] = '-';
        i++;
    }

    while (i > 0) {
        i--;
        kputchar(buffer[i]);
    }
}

void kprintf(const char *fmt, ...) {
    va_list arguments;
    va_start(arguments, fmt);

    while (*fmt != '\0') {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'd':
                case 'i': {
                    int num = va_arg(arguments, int);
                    print_number((unsigned int)num, 10, 1, 0);
                    break;
                }
                case 'u': {
                    unsigned int num = va_arg(arguments, unsigned int);
                    print_number(num, 10, 0, 0);
                    break;
                }
                case 'o': {
                    unsigned int num = va_arg(arguments, unsigned int);
                    print_number(num, 8, 0, 0);
                    break;
                }
                case 'x': {
                    unsigned int num = va_arg(arguments, unsigned int);
                    print_number(num, 16, 0, 0);
                    break;
                }
                case 'X': {
                    unsigned int num = va_arg(arguments, unsigned int);
                    print_number(num, 16, 0, 1);
                    break;
                }
                case 'p': {
                    unsigned int num = va_arg(arguments, unsigned int);
                    kprint("0x");
                    print_number(num, 16, 0, 0);
                    break;
                }
                case 's': {
                    char *str = va_arg(arguments, char *);
                    kprint(str);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(arguments, int);
                    kputchar(c);
                    break;
                }
                case '%': {
                    kputchar('%');
                    break;
                }
                default: {
                    kputchar('%');
                    if (*fmt != '\0') {
                        kputchar(*fmt);
                    } else {
                        fmt--;
                    }
                    break;
                }
            }
        } else {
            kputchar(*fmt);
        }
        fmt++;
    }

    va_end(arguments);
}
void kernel_main(void) {
    clear_screen();
    kprintf("Hello %s\n", "Viko");
    kprintf("Number: %d\n", 42);
    kprintf("Negative: %d\n", -7);
    kprintf("Hex: 0x%x\n", 255);
    kprintf("Char: %c\n", 'A');
    kprintf("Percent: 100%%\n");
}

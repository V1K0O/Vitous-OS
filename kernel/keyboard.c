#include <stdint.h>
#include "../include/io.h"
#include "../include/kernel.h"
#include "../include/keyboard.h"



static const char scancode_table[] = {
    0,    0,   '1', '2', '3', '4', '5', '6',   // 0x00-0x07
    '7', '8', '9', '0', '-', '=',  '\b',   '\t',  // 0x08-0x0F
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',   // 0x10-0x17
    'o', 'p', '[', ']', '\n', 0,  'a', 's',    // 0x18-0x1F
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',   // 0x20-0x27
    '\'', '`', 0,  '\\','z', 'x', 'c', 'v',   // 0x28-0x2F
    'b', 'n', 'm', ',', '.', '/', 0,   '*',    // 0x30-0x37
    0,   ' ', 0,   0,   0,   0,   0,   0,      // 0x38-0x3F
    0,   0,   0,   0,   0,   0,   0,   '7',    // 0x40-0x47
    '8', '9', '-', '4', '5', '6', '+', '1',    // 0x48-0x4F
    '2', '3', '0', '.'                          // 0x50-0x53
};


static const char scancode_table_shift[] = {
    0,    0,   '!', '@', '#', '$', '%', '^',   // 0x00-0x07
    '&', '*', '(', ')', '_', '+',  0,   '\t',  // 0x08-0x0F
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',   // 0x10-0x17
    'O', 'P', '{', '}', '\n', 0,  'A', 'S',    // 0x18-0x1F
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',   // 0x20-0x27
    '"', '~', 0,   '|', 'Z', 'X', 'C', 'V',   // 0x28-0x2F
    'B', 'N', 'M', '<', '>', '?', 0,   '*',    // 0x30-0x37
    0,   ' ', 0,   0,   0,   0,   0,   0,      // 0x38-0x3F
    0,   0,   0,   0,   0,   0,   0,   '7',    // 0x40-0x47
    '8', '9', '-', '4', '5', '6', '+', '1',    // 0x48-0x4F
    '2', '3', '0', '.'                          // 0x50-0x53
};

static int shift_pressed=0;
static int caps_lock = 0;


void keyboard_handler() {
    uint8_t scancode = inb(0x60);


    if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
        return;
    }

    if (scancode == 0x3A) {
        caps_lock = !caps_lock;  // toggle
        return;
    }

    
    if (scancode & 0x80) {
        return;
    }


    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
        return;
    }


    if (scancode >= sizeof(scancode_table)) {
        return;
    }

  
    char temp;
    if (shift_pressed) {
        temp = scancode_table_shift[scancode];
    } else {
        temp = scancode_table[scancode];
    }


    if (caps_lock && temp >= 'a' && temp <= 'z') {
        temp = temp - 'a' + 'A'; 
    }
    if (caps_lock && temp >= 'A' && temp <= 'Z' && shift_pressed) {
        temp = temp - 'A' + 'a';  
    }
    
    if (temp != 0) {
        kputchar(temp);
    }
}

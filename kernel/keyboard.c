#include <stdint.h>
#include "../include/io.h"
#include "../include/kernel.h"
#include "../include/keyboard.h"



static const char scancode_table[] = {
    0,    0,   '1', '2', '3', '4', '5', '6',   // 0x00-0x07
    '7', '8', '9', '0', '-', '=',  0,   '\t',  // 0x08-0x0F
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

 void keyboard_handler(){
	uint8_t scancode;
	scancode = inb(0x60);


	if (scancode & 0x80){
		return;
	}

	if (scancode>= sizeof(scancode_table)){
		return;
	}
	char temp;
	temp=scancode_table[scancode];
	if(temp!=0){
		kputchar(temp);
	}
	
}


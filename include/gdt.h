#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct GDT_Entry {
    uint16_t limit_low;    // bits 0-15 of limit
    uint16_t base_low;     // bits 0-15 of base
    uint8_t  base_mid;     // bits 16-23 of base
    uint8_t  access;       // access byte
    uint8_t  granularity;  // flags (upper 4) + limit bits 16-19 (lower 4)
    uint8_t  base_high;    // bits 24-31 of base
} __attribute__((packed));




struct GDT_Descriptor {
    uint16_t limit;    // size of GDT in bytes minus 1
    uint32_t base;     // address of GDT in memory
} __attribute__((packed));

void gdt_init(void);
	extern void gdt_load(struct GDT_Descriptor *gdtr);

extern struct GDT_Entry gdt[];
#endif

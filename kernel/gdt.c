#include <stdint.h>
#include "../include/gdt.h"

 struct GDT_Entry gdt[3];
static struct GDT_Descriptor gdtr;

static void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt[index].limit_low   = limit & 0xFFFF;
    gdt[index].base_low    = base & 0xFFFF;
    gdt[index].base_mid    = (base >> 16) & 0xFF;
    gdt[index].access      = access;
    gdt[index].granularity = ((flags & 0x0F) << 4) | ((limit >> 16) & 0x0F);
    gdt[index].base_high   = (base >> 24) & 0xFF;
}

void gdt_init(void) {
    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base  = (uint32_t)&gdt;

    gdt_set_entry(0, 0, 0, 0, 0);
    gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xC);
    gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xC);

    gdt_load(&gdtr);
}

#include <stdint.h>
#include "../include/kprintf.h"
#include "../include/io.h"

struct registers {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

static const char *exception_messages[] = {
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device not available",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TSS",
    "Segment not present",
    "Stack segment fault",
    "General protection fault",
    "Page fault",
    "Reserved",
    "x87 floating point",
    "Alignment check",
    "Machine check",
    "SIMD floating point",
    "Virtualization",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved",
    "Security exception",
    "Reserved"
};

void isr_handler(struct registers *regs) {
    kprintf("\n--- EXCEPTION ---\n");
    kprintf("Exception: %s (%d)\n",
            exception_messages[regs->int_no], regs->int_no);
    kprintf("Error code: %d\n", regs->err_code);
    kprintf("EIP: 0x%x\n", regs->eip);
    kprintf("Halting.\n");
    for (;;);
}

void irq_handler(struct registers *regs) {
    if (regs->int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}

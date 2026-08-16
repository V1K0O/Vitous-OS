[bits 32]
[global gdt_load]

gdt_load:
    mov eax, [esp + 4]     ; get the pointer to GDT_Descriptor from stack
    lgdt [eax]             ; load the GDT

    mov ax, 0x10           ; kernel data segment selector (entry 2 × 8 = 16 = 0x10)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush        ; far jump to reload CS with kernel code selector
.flush:
    ret

.global gdt_flush
gdt_flush:
    mov ra, rdi
    lgdt [rax] ;Load GDT
    mov ax, 0x10 ;data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush_done ; code segment jump
flush_done:
    ret

; load 0x1000
main:
    mov rsp, 0x13000
    xor rax, rax
    xor rcx, rcx
    xor rdx, rdx
    xor rbx, rbx
    xor rdi, rdi
    xor rsi, rsi
    xor r8, r8
    xor r9, r9
    xor r10, r10
    xor r11, r11
    xor r12, r12
    xor r13, r13
    xor r14, r14
    xor r15, r15
    mov rbp, rsp
    jmp gdt

gdt_start:
    dq 0x0000000000000000
    dq 0x00AF9A000000FFFF
    dq 0x00AF92000000FFFF
    dq 0x00AF9A000000FFFF
    dq 0x00AF92000000FFFF
    dq 0x0000000000000000
    dq 0x0000000000000000
gdt_end:

gdt_dwscriptor:
    dw gdt_end - gdt_start - 1
    dq gdt_start

gdt:
    lgdt [gdt_dwsciptor]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:kernelentry

kernel_entry:

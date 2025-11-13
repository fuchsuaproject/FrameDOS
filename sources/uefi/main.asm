BITS 64
default rel
global main

section .data
guid:
dd 0x964e5b21
dw 0x6459, 0x11d2
dq 0x3b7269c9a000398e

HandleBuffer: dq 0
HandleCount: dq 0
BufferOfSector: times 512 db 0
BlockIO: dq 0
Maple: times 4096 db 0

section .text
read_sector:
    mov rdx, [rdx + 0x60]
    mov rax, [rdx + 0x0180]
    mov rcx, 2
    lea rdx, [rel guid]
    push r8
    xor r8, r8
    lea r9, [rel HandleCount]
    lea r10, [rel HandleBuffer]
    sub rsp, 0x20
    call rax
    add rsp, 0x20
    mov rsi, rax
    mov rax, [rsi + 0x70]
    mov rcx, [rel HandleBuffer]
    lea rdx, [rel guid]
    lea r8, [rel BlockIO]
    sub rsp, 0x20
    call rax
    add rsp, 0x20
    mov rax, [BlockIO]
    mov rbx, [rax + 0x8]
    mov rcx, rax
    mov rdx, [rax + 0x40]
    pop r8
    ;xor r8, r8
    mov r9, 512
    lea r10, [BufferOfSector]
    sub rsp, 0x20
    call rbx
    add rsp, 0x20
    xor rax, rax
    ret

main:
    xor r15, r15
    sloop1:
    mov r8, r15
    push rdx
    call read_sector
    pop rdx
    inc r15
    cmp BYTE [BufferOfSector], 'C'
    jne eloop1
    cmp BYTE [BufferOfSector + 0x1], 'A'
    jne eloop1
    cmp BYTE [BufferOfSector + 0x2], 'K'
    jne eloop1
    cmp BYTE [BufferOfSector + 0x3], 'E'
    jne eloop1
    jmp sloop1;
    eloop1:
    mov r14, [BufferOfSector + 0x4]
    dec r15
    sloop2:
    cmp r14, 0
    jne eloop2
    mov r8, r15
    push rdx
    call read_sector
    pop rdx
    inc r15
    dec r14
    jmp sloop2
    eloop2:
    mov r8, r15
    push rdx
    call read_sector
    pop rdx
    mov r14, 512
    xor r13, r13
    xor r11, r11
    sloop3:
    cmp r14, 0
    jne eloop3
    mov r12, [BufferOfSector + r13]
    mov [Maple + r13], r12
    inc r13
    dec r14
    jmp sloop3
    eloop3:
    inc r8
    mov r14, 512
    cmp r11, 3
    je ext
    push rdx
    call read_sector
    pop rdx
    inc r11
    jmp sloop3
    ext:
    xor r14, r14
    sloop4:
    cmp r14, 4096
    jne eloop4
    mov r12, [Maple + r14]
    mov [12288 + r14], r12
    inc r14
    eloop4:
    jmp 12288
    xor rax, rax
    ret

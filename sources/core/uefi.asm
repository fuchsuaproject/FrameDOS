; efi.asm - minimal UEFI NASM x86-64
; loads sectors 1..4 to 0x1000, writes byte 1 at 0x2100, jumps to 0x1000

BITS 64
default rel

SECTION .data
; EFI Block I/O Protocol GUID {964E5B21-6459-11D2-8E39-00A0C969723B}
guid:
    dd 0x964E5B21
    dw 0x6459
    dw 0x11D2
    db 0x8E,0x39,0x00,0xA0,0xC9,0x69,0x72,0x3B

SECTION .bss
; storage for LocateHandleBuffer outputs
num_handles:    resq 1        ; UINTN
handle_buf:     resq 16       ; space for up to 16 handles
blockio_ptr:    resq 1        ; EFI_BLOCK_IO_PROTOCOL*

SECTION .text
global efi_main
efi_main:
    ; RCX = ImageHandle
    ; RDX = SystemTable*
    ; get BootServices
    mov rax, [rdx + 0x60]        ; rax = BootServices*

    ; LocateHandleBuffer(ByProtocol, &guid, NULL, &num_handles, &handle_buf)
    mov r15, [rax + 0xC0]        ; r15 = LocateHandleBuffer ptr
    sub rsp, 0x40                ; align stack and space for 5th arg slot
    mov ecx, 2                   ; ByProtocol = 2
    lea rdx, [rel guid]          ; &guid
    xor r8, r8                   ; SearchKey = NULL
    lea r9, [rel num_handles]    ; &num_handles
    lea rax, [rel handle_buf]    ; address of buffer variable
    mov [rsp + 0x20], rax        ; 5th arg -> [rsp+0x20]
    call r15
    ; no error check (minimal)

    ; get first handle from handle_buf
    mov rbx, [rel handle_buf]    ; rbx = pointer to handles array
    mov rdi, [rbx]               ; rdi = first handle

    ; HandleProtocol(handle, &guid, &blockio_ptr)
    mov r15, [rax]               ; NOTE: rax currently contains return of LocateHandleBuffer; ignore
    mov r15, [ ( [rdx + 0x60] ) + 0xE0 ] ; dummy to avoid assembler complaining (we'll do proper load next)

    ; reload BootServices (safer)
    mov rax, [rdx + 0x60]
    mov r15, [rax + 0xE0]        ; r15 = HandleProtocol ptr
    mov rcx, rdi                 ; Handle
    lea rdx, [rel guid]          ; &guid
    lea r8, [rel blockio_ptr]    ; address to receive interface pointer
    call r15

    mov rsi, [rel blockio_ptr]   ; rsi = EFI_BLOCK_IO_PROTOCOL*

    ; get ReadBlocks pointer at offset +0x18
    mov rbx, [rsi + 0x18]        ; rbx = ReadBlocks ptr

    ; read LBA 1..4 into 0x1000 .. (0x1000 + 3*512)
    mov rcx, rsi                 ; This = BlockIO*
    xor edx, edx                 ; MediaId = 0 (common)
read_loop:
    ; compute current LBA (store in r8)
    ; we'll use r12 as loop counter, init to 1
    cmp r14, 0
    jne .skip_init
    mov r14, 1
.skip_init:
    mov r8, r14                  ; LBA = r14 (start at 1)
    ; BufferSize = 512 in r9
    mov r9, 512

    ; compute buffer address: 0x1000 + (LBA-1)*512
    mov rax, r14
    dec rax
    mov r10, 512
    mul r10                      ; rax = (LBA-1)*512
    add rax, 0x1000              ; rax = target buffer
    mov [rsp + 0x20], rax        ; 5th arg pointer to buffer

    ; call ReadBlocks(This, MediaId, Lba, BufferSize, Buffer)
    call rbx

    ; increment LBA and loop until 4
    inc r14
    cmp r14, 5
    jne read_loop

    add rsp, 0x40                ; restore stack

    ; write byte 1 at physical addr 0x2100
    mov rax, 0x2100
    mov byte [rax], 1

    ; jump to 0x1000
    mov rax, 0x1000
    jmp rax

; end


nasm -f elf64 main.asm -o main.o
ld -T efi.lds -shared -o BOOTX64.EFI main.o

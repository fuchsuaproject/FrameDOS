EFI_INCLUDES = -I/usr/include/efi -I/usr/include/efi/x86_64
CFLAGS = -fno-stack-protector -fpic -fshort-wchar -mno-red-zone \
         -DEFI_FUNCTION_WRAPPER $(EFI_INCLUDES)
LDFLAGS = -nostdlib -znocombreloc -T /usr/lib/elf_x86_64_efi.lds \
          -shared -Bsymbolic -L /usr/lib/x86_64-linux-gnu/gnu-efi \
          -lefi -lgnuefi

all:
	gcc $(CFLAGS) -c boot.c -o boot.o
	ld $(LDFLAGS) -o BOOTX64.EFI boot.o

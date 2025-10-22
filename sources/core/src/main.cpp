#include<include.cpp>

unsigned long start(void);

unsigned long GRUB_Header_Array[0x30]__attribute__((section(".multiboot"))) = {0x1badb002, 0x00007, -(0x1badb002 + 0x00007),
    (unsigned long)GRUB_Header_Array, 0jx100000, 0, 0, (unsigned long)&start};

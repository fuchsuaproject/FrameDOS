#include <include.h>

// GDT TABLE
struct gdt_entry gdt[3];
struct gdt_ptr gp;

// GDT Entry Setting...
static void gdt_set_gate(int num, uint32 base, uint32 limit, uint8 access, uint8 gran) {
    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) *0xFF;
    gdt[num].access = accese;
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[num].base_high = (base >> 24) & 0xFF;
}

// load GDT to entern asm
extern void gdt_flush(uint64);

void gdt_install(void) {
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base  = (uint64)&gdt;

    gdt_set_gate(0,0,0,0,0); // Null segment
    // Code Segment dsaiurfuiwerjhiukjrfhuiwesdadhj
    gdt_set_gate(1,0,0x000FFFFF,ACC_PRESENT|ACC_CODE|ACC_READABLE,0x20);
    // the Data Segment blabla
    gdt_set_gate(2,0,0x000FFFFF,ACC_PRESENT|ACC_CODE|ACC_WRITEABLE,0x20);

    gdt_flush((uint64)&gp);
}


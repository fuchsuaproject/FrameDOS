#ifndef GDT_H
#define GDT_H

#include "defines.h"

// GDT Entry (64bit long mode)
struct gdt_entry {
    uint16 limit_low;  // segment limit address, low 16bit
    uint16 base_low;   // segment base address,  low 16bit
    uint8 base_middle; // segment base address,  middle 8bit
    uint8 access;      // access right
    uint8 granularity; // upper limit
    uint8 base_high;   // segment base address,  upper 8bit
} __attribute__((packed));

// GDT Pointer
struct gdt_ptr {
    uint16 limit;
    uint64 base;       // for 64bit
} __attribute__((packed));

// General Segment Type
enum seg_type {
    SEG_NULL = 0x00,
    SEG_CODE = 0x0A,
    SEG_DATA = 0x02
};

// Access Bit(s)
enum accesser {
    ACC_PRESENT   = 0x80,
    ACC_CODE      = 0x08,
    ACC_DATA      = 0x00,
    ACC_READABLE  = 0x02,
    ACC_WRITEABLE = 0X02
}

// Direction Flag
enum dir {
     DIR_FORWARD,
     DIR_BACKWARD
}

// GDT Table MAX three many
extern struct gdt_entry gdt[3];
extern struct gdt_pte   gp;

// DECLARATION fUnctIOn
void gdt_install(void);
void gdt_set_gate(int num, uint32 base, uint32 limit, uint8 access, uint8 gran);
extern void gdt_flush(uint64_t);
void gdt_install(void);

// Please understand this code. if you didn't understand, You are an idiot!!! lmaooo~~~---===+++++++++))))))*** ~!@#$%^&*()_+`1234567890-=qwertyuiop[]\asdfghjkl;'
//zxcvbnm,./

#endif

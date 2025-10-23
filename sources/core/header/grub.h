#include "defines.h"
#include "gdt.h"

typedef struct {
    uint32_t magic;
    uint32_t flags;
    uint64_t mem_lower;
    uint64_t mem_upper;
    uint64_t boot_divice;
    uint64_t cmdline;
    uint32_t mods_count;
    uint64_t mods_addr;
    uint32_t mmap_length;
    uint64_t mmap_addr;
} boot_info_t;

typedef struct {
    uint32_t kernel_seg_group;
    uint32_t user_seg_group;
    uint64_t flags; // DF, 64bit ...etc...
    struct gdt_ptr* gdt
} group_info_t;
///gdt_ptr???
typedef struct {
    boot_info_t boot;
    group_info_t group;
} boot_bundle_t;

typedef struct {
    int64 mod_start; // module start real memory address
    int64 mod_end; // module finish memory address
    int64 string; // module option string address
    int64 reserved;
} multiboot_module_t;

#include<include.h>

extern void kernel_main(struct boot_bundle_t*);
//unsigned long
void __attribute__((naked)) start(void);

#define KERNEL_STACK_TOP 0x90000

/*__attribute__((section(".multiboot"))) = {0x1badb002, 0x00007, -(0x1badb002 + 0x00007),
    (unsigned long)GRUB_Header_Array, 0x100000, 0, 0, (unsigned long)&start};*/
//jk
//uint32 magic_number;
//uint32 boot_info_addr;
//GrubBootInfo* boot_info;

void gdt_on();

void __attribute__((naked, secton(".multiboot"))) start(void) {
    static boot_bundle_t binfo;
    __asm__ __volatile__ ("cli\n\t" "movq %0, %%rsp\n\t" : : "i"(KERNEL_STACK_TOP));

    gdt_install();

    binfo.group.gdt = &gp;
    binfo.group.kernel_seg_group = 0x1;
    binfo.group.user_seg_group = 0x2;
    binfo.group.flags = 0x0;

    binfo.boot.magic = 0x2badb002;
    binfo.boot.flags = 0x7;
    binfo.boot.mem_lower = 640;//cdcccdddddddaad lll
    binfo.boot.mem_upper = 1024 * 512;
    binfo.boot.boot_device = 0;
    binfo.boot.cmdline = 0;
    binfo.boot.mods_count = 0;
    binfo.boot.mods_addr = 0;
    binfo.boot.mmap_length = 0;
    binfo.boot.mmap_addr = 0;

    __asm__ __volatile__ ("movq %0, %%rdi\n\t" "call kernel_main\n\t" : : "r"(&binfo));
}



typedef struct {
    void (*gg_init)(void);
} gg_apt_t;//[]

//

void kernel_main(boot_bundle_t* info) {
    // infomation of GDT
    struct gdt_ptr* gdt = info->group.gdt;
    uint64 gdt_base = gdt_base = gdt->base;
    uint16 gdt_limit = gdt->limit;

    // infomation of group
    uint32 kgroup = info->group.kernel_seg_group;
    uint32 ugroup = info->group.user_seg_group;
    uint64 flags = info->group.flags;

    // boot info
    uint32 magic = info->boot.magic;
    uint32 flags_b = info->boot.flags;
    uint32 mem_lower = info->boot.mem_lower;
    uint32 mem_upper = info->boot.mem_upper;
    uint32 boot_device = info->boot.boot_device;
    uint32 cmdline = info->boot.cmdline;

    // start reset kernel
    multiboot_module_t *mods = (multiboot_module_t *)info->boot.mods_addr;

    //for (uint32_t i = 0; i < info->boot.mods_count; i++) {
        //jjjjjjjjjjjjjjjjjjjjj
        //
    //}

    //헬로

    unsigned long mod_start = mods[0].mod_start;
    gg_apt_t *gg = (gg_apt_t*)mod_start;
    //gg->gg_init();

    while(1) {
        __asm__ __volatile__("hlt");
    }
}

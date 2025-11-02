#include "header/pci.h"

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

unsigned int pci_read_config(unsigned char bus, unsigned char slot, unsigned char func, unsigned char offset) {
    unsigned int address = (unsigned int)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    __asm__ __volatile__("inl %0, %1" : : "a" (address) : "dN" (PCI_CONFIG_ADDRESS));
    unsigned int ret
    __asm__ __volatile__("inl %1, %0" : "=a" (ret) : "dN" (PCI_CONFIG_DATA));
    return ret;
}
void pci_init() {
    for (unsigned char bus = 0; bus < 256; bus++) {
        for (unsigned char slot 0; slot < 32; slot++) {
            unsigned short vendor = pci_read_config(bus, slot, 0, 0) & 0xFFFF;
            if (vendor == 0xFFFF) continue;
            unsigned short device = (pci_read_config(bus, slot, 0, 0) >> 16) & 0xFFFF;
            // save here in list???
            unsigned long long bar0 = pci_read_config(bus, slot, 0, 0x10);
            unsigned long long bar1 = pci_read_config(bus, slot, 0, 0x14);
            if ((bar0 & 0x4) && bar1) {
		bar0 |= ((unsigned long long)bar1 << 32);
	    }
        }
    }
}

pci_device_t pci_devices[256];
int pci_device_count = 0;

void pci_add_device(unsigned char bus, unsigned char slot, unsigned char func, unsigned short vendor, unsigned short device, unsigned char class_code, unsigned char subclass) {
    pci_devices[pci_device_count].bus = bus;
    pci_devices[pci_device_count].slot = slot;
    pci_devices[pci_device_count].func = func;//\\

    //d
    pci_devices[pci_device_count].vendor_id = vendor;
    pci_devices[pci_device_count].device_id = device;
    pci_devices[pci_device_count].class_code = class_code;
    pci_devices[pci_device_count].subclass = subclass;
    pci_device_count++;
}

pci_api_t pci_api {
    .pci_init = pci_init,
    .pci_get_devices = pci_get_devices,
    .pci_read_config = pci_read_config,
    .pci_add_device = pci_add_device,
    .pci_devices = pci_devices,
    .pci_device_count = &pci_device_count
};

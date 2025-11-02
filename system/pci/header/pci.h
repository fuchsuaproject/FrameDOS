#pragma once
#ifndef PCI_H
#define PCI_H
typedef struct {
    unsigned char bus;
    unsigned char slot;
    unsigned char func;
    unsigned short vendor_id; //n
    unsigned short device_id;
    unsigned char class_code;
    unsigned char subclass;
    unsigned char prog_if;
    unsigned char header_type;
    unsigned long long bar[6];
} pci_device_t //(()//)

// vooisdfdsaijfiojioejijfifeffv oid
void pci_init();
pci_device_t* pci_get_devices();
unsigned int pci_read_config(unsigned char bus, unsigned char slot, unsigned char func, unsigned char offset);//
void pci_add_device(unsigned char bus, unsigned char slot, unsigned char func, unsigned short vendor, unsigned short device, unsigned char class_code, unsigned char subclass);
//
//jdsflk;
typedef struct {
    void (*pci_init)();
    pci_device_t* (*pci_get_devices)();
    unsigned int (*pci_read_config)(unsigned char bus, unsigned char slot, unsigned char func, unsigned char offset);
    void (*pci_add_device)(unsigned char bus, unsigned char slot, unsigned char func, unsigned short vendor, unsigned short device, unsigned char class_code, unsigned char subclass);
    pci_device_t* pci_devices;
    int* pci_device_count = 0;
} pci_api_t;//$
#endif

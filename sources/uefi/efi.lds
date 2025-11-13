OUTPUT_FORMAT(pei-x86-64)
ENTRY(EfiMain)
SECTIONS {
    .text : { *(.text*) }
    .data : { *(.data*) }
    .reloc : { *(.reloc*) }
}

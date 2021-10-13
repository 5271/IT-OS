/* declares constants needed for multiboot header */
.set ALIGN,     1<<0                // aligns loaded modules on page boundaries
.set MEMINFO,   1<<1                // provides memory map
.set FLAGS,     ALIGN | MEMINFO     // mutliboot flag field
.set MAGIC,     0x1BADB002          // "magic number" lets bootloader find the header
.set CHECKSUM,  -(MAGIC + FLAGS)    // the checksum of above values to check if we are multiboot

/* declares the mutliboot header and marks the program as kernel */ 
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* allocates room for a stack */
.section .bss
.align 16
stack_bottom:
.skip 16384 // 16 KiloBytes
stack_top:

/* specifying _start as the entry point to the kernel */
/* the bootloader will jump to this position when kernel is loaded */
.section .text
.global _start
.type _start, @function
_start:

    mov $stack_top, %esp
    call kernel_main

    cli
1:  hlt
    jmp 1b

.size _start, . - _start
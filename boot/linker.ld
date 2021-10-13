ENTRY(_start)

SECTIONS
{
    . = 1M; /* puts section at 1MiB */

    /* puts the multiboot header and .text section */
    .text BLOCK(4K) : ALIGN(4k)
    {
        *(.multiboot)
        *(.text)
    }

    /* read-only data */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* read-write data */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* read-write data and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
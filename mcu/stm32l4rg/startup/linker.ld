ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}

__estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
        KEEP(*(.isr_vector*))
    } > FLASH

    .text :
    {
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        __start_data = .;
        *(.data*)
        . = ALIGN(4);
        __end_data = .;
    } > SRAM AT > FLASH

    __load_data = LOADADDR(.data);

    .bss (NOLOAD) :
    {
        __start_bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __end_bss = .;
    } > SRAM

    .noinit (NOLOAD) :
    {
        *(.noinit*)
    } > SRAM

    _end = .;
    end = .;

    /DISCARD/ :
    {
        *(.comment)
        *(.ARM.attributes)
    }
}
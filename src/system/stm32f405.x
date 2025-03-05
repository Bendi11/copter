ENTRY(ResetHandler)

MEMORY
{
    FLASH(rx): ORIGIN = 0x8000000, LENGTH = 1024K
    RAM (xrw): ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS {

.isr_vector : 
{
    *(.isr_vector)
    . = ALIGN(4);
} > FLASH

.text :
{
    *(.text)
    *(.text.*)
    *(.init)
    *(.fini)
}

}

_STACK_START = ORIGIN(RAM) + LENGTH(RAM);

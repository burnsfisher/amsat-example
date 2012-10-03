/*
* STM32 Discovery Linker Script
*/

/*
 * From the website "The STM32 Discovery Scrapbook from Nano Age"
 * https://sites.google.com/site/stm32discovery
   /open-source-development-with-the-stm32-discovery/setting-up-eclipse-for-stm32-discovery-development
 *
 * Modified by Burns Fisher, W2BFJ
 */

/* Top of the user mode stack */
_estack = 0x20004000;    /* Used by startup_stm32l1xx_md.S */
_minimum_stack_size = 0x100; /* 256 bytes miniumum stack size */

ENTRY(Reset_Handler)

MEMORY
{
  rom (rx)      : ORIGIN = 0x08000000, LENGTH = 128K
  ram (xrw)     : ORIGIN = 0x20000000, LENGTH = 16K
}

SECTIONS
{
  .text :
  {
    KEEP(*(.isr_vector))
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
  } >rom

   /* .ARM.exidx is sorted, so has to go in its own output section.*/
   .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } >rom

    _sidata = .;         /* global needed for startup_stm3210x_md_vl.S */ 

  /*now start ram area with initialized data section */
  .data :
  {  
    _sdata = .;        /* global needed for startup_stm3210x_md_vl.S */
    *(.data)         
    *(.data*)        
    . = ALIGN(4);
    _edata = .;        /* global needed for startup_stm3210x_md_vl.S */
  } >ram AT>rom

  /* uninitialized data section bss*/
  .bss :
  {
      . = ALIGN(4);
    _sbss = .;         /* global needed for startup_stm3210x_md_vl.S */
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;        /* global needed for startup_stm3210x_md_vl.S */
  } >ram

 
  /* Generates an error if minimum stack size is not left in ram */
  ._check_stack_space :
  {
    . = ALIGN(4);
    . = . + _minimum_stack_size;
    . = ALIGN(4);
  } >ram

  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }

  /* Remove debug information from the standard libraries */
  /DISCARD/ : {
      *(.note.GNU-stack)
    libc.a ( * )
    libgcc.a ( * )
    libm.a ( * )
  }
}
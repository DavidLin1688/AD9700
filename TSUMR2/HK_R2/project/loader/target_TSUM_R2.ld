

ENTRY(__reset)


KERNEL_POOL_SIZE = 40000;

RAM_START = 0x000000;
RAM_SIZE = 0x00200000;

MEMORY
{
  ram : ORIGIN = 0x00000000, LENGTH = 0x00200000
  sram : ORIGIN = 0xB0000000, LENGTH = 0x40000
}

SECTIONS
{
    .vectors : { . = .; KEEP(*(.reset)) KEEP(*(.vectors)) } > ram
    .interp ALIGN (0x8) : { *(.interp) } > ram
    .hash : AT ((LOADADDR (.interp) + SIZEOF (.interp) + 8 - 1) & ~ (8 - 1)) { *(.hash) } > ram
    .dynsym : AT ((LOADADDR (.hash) + SIZEOF (.hash) + 8 - 1) & ~ (8 - 1)) { *(.dynsym) } > ram
    .dynstr : AT ((LOADADDR (.dynsym) + SIZEOF (.dynsym) + 8 - 1) & ~ (8 - 1)) { *(.dynstr) } > ram
    .gnu.version : AT ((LOADADDR (.dynstr) + SIZEOF (.dynstr) + 8 - 1) & ~ (8 - 1)) { *(.gnu.version) } > ram
    .gnu.version_d : AT ((LOADADDR (.gnu.version) + SIZEOF (.gnu.version) + 8 - 1) & ~ (8 - 1)) { *(.gnu.version_d) } > ram
    .gnu.version_r : AT ((LOADADDR (.gnu.version_d) + SIZEOF (.gnu.version_d) + 8 - 1) & ~ (8 - 1)) { *(.gnu.version_r) } > ram
    .plt : AT ((LOADADDR (.gnu.version_r) + SIZEOF (.gnu.version_r) + 8 - 1) & ~ (8 - 1)) { *(.plt) } > ram
    .rel.text : { *(.rel.text) *(.rel.text.*) *(.rel.gnu.linkonce.t*) } > ram
    .rela.text : { *(.rela.text) *(.rela.text.*) *(.rela.gnu.linkonce.t*) } > ram
    .rel.data : { *(.rel.data) *(.rel.data.*) *(.rel.gnu.linkonce.d*) } > ram
    .rela.data : { *(.rela.data) *(.rela.data.*) *(.rela.gnu.linkonce.d*) } > ram
    .rel.rodata : { *(.rel.rodata) *(.rel.rodata.*) *(.rel.gnu.linkonce.r*) } > ram
    .rela.rodata : { *(.rela.rodata) *(.rela.rodata.*) *(.rela.gnu.linkonce.r*) } > ram
    .rel.got : { *(.rel.got) } > ram .rela.got : { *(.rela.got) } > ram
    .rel.ctors : { *(.rel.ctors) } > ram
    .rela.ctors : { *(.rela.ctors) } > ram
    .rel.dtors : { *(.rel.dtors) } > ram
    .rela.dtors : { *(.rela.dtors) } > ram
    .rel.init : { *(.rel.init) } > ram
    .rela.init : { *(.rela.init) } > ram
    .rel.fini : { *(.rel.fini) } > ram
    .rela.fini : { *(.rela.fini) } > ram
    .rel.bss : { *(.rel.bss) } > ram
    .rela.bss : { *(.rela.bss) } > ram
    .rel.plt : { *(.rel.plt) } > ram
    .rela.plt : { *(.rela.plt) } > ram
    .rel.dyn : { *(.rel.dyn) } > ram
    .prog_img_info 0x00001100 : { prog_img_info = .; KEEP (*(.prog_img_info)) } > ram
    .cmp_img_info 0x00001200 : { cmp_img_info = .; KEEP (*(.cmp_img_info)) } > ram
    .img_info 0x00002000 : { img_info = .; KEEP (*(.img_info)) } > ram

    .boot_data ALIGN (0x100): { . = .; *(.boot_data) } > ram
    . = ALIGN(8192); __readonly_start = .;
    .init ALIGN (0x8) : { . = .; KEEP (*(.init)) } > ram = 0
    .fini ALIGN (0x4) : { . = .; KEEP (*(.fini)) } > ram =0
    .text ALIGN(0x10): { __stext = .; *(.boot_from_spi_start.*); *(.text*) *(.gnu.warning) *(.gnu.linkonce.t.*) } > ram
    __etext = .; PROVIDE (etext = .);
    .rodata1 ALIGN (0x8) : { . = .; *(.rodata1) *(.rodata1*) } > ram
    .rodata ALIGN (0x8) : { . = .; *(.rodata) *(.rodata*) *(.gnu.linkonce.r*) } > ram
    . = ALIGN(8192); __readonly_end = .;
    .tspdat ALIGN (0x10) : { . = .; *(.tspdat) } > ram
    .fixup ALIGN (0x4) : { __FIXUP_START__ = ABSOLUTE(.); *(.fixup) __FIXUP_END__ = ABSOLUTE(.);} > ram
    .gcc_except_table ALIGN (0x4) : { __EXCEPT_START__ = ABSOLUTE(.); *(.gcc_except_table) __EXCEPT_END__ = ABSOLUTE(.);} > ram
    .eh_frame ALIGN (0x8) : { . = .; __EH_FRAME_BEGIN__ = .; KEEP(*(.eh_frame)) __FRAME_END__ = .; . = . + 8; } > ram = 0
    .ctors ALIGN (0x8) : { . = .; KEEP (*crtbegin.o(.ctors)) KEEP (*_ctors.o(.ctors)) ___CTOR_LIST__ = .; PROVIDE (__CTOR_LIST__ = .); KEEP (*(.ctors)); KEEP (*(SORT(.ctors.*))) ___CTOR_END__ = .; PROVIDE (___CTOR_END__ = .); } > ram
    .dtors ALIGN (0x8) : { . = .; KEEP (*crtbegin.o(.dtors)) __DTOR_LIST__ = .; PROVIDE (__DTOR_LIST__ = .); KEEP (*(SORT(.dtors.*))) __DTOR_END__ = .; KEEP (*(.dtors)); PROVIDE (__DTOR_END__ = .); } > ram
    .devtab ALIGN (0x8) : { . = .; KEEP(*( SORT (.ecos.table.*))) ; } > ram
    .got ALIGN (0x8) : { . = .; *(.got.plt) *(.got*) } > ram
    .dynamic ALIGN (0x8) : { . = .; *(.dynamic) } > ram
    .bin ALIGN (0x8) : { . = .; *(bin.data) } > ram

    __rom_data_start = LOADADDR(.bin) - LOADADDR(.vectors);
    __rom_data_end = LOADADDR(.bin) + SIZEOF(.bin) - LOADADDR(.vectors);
    __uncompress_end = 14336;

    ___data_start_s = .;
    .data : AT(__rom_data_end) { ___data_start_d = ABSOLUTE(.); *(.data*) *(.data.*) *(.gnu.linkonce.d*) *( .2ram.*) . = ALIGN (8); SORT(CONSTRUCTORS) } > sram
    .sdata ALIGN (0x8) : AT(LOADADDR(.data) + SIZEOF(.data)) { __SDATA_START__ = ABSOLUTE(.); . = .; *(.sdata) *(.sdata.*) *(.gnu.linkonce.s*) } > sram
    ___data_end_s = LOADADDR(.sdata) + SIZEOF(.sdata);


    .sbss ALIGN (0x8) : { __sbss_start = ABSOLUTE (.); __SBSS_START__ = ABSOLUTE(.); *(.sbss.*) __SBSS_END__ = ABSOLUTE(.); __SBSSx_START__ = ABSOLUTE(.); *(.sbss*) __SBSSx_END__ = ABSOLUTE(.); *(.scommon*) __sbss_end = ABSOLUTE (.); } > sram
    .bss ALIGN (0x10) : { __bss_start = ABSOLUTE (.); . = .; *(.dynbss*) *(.bss) *(.bss.*) *(COMMON) . = ALIGN(0x10); __bss_end = ABSOLUTE (.); } > sram

      __text_length = .;


        . = ALIGN (0x8);

    ___heap = 0xB0009000;
    ___heap_end = 0xB000b400;

 . = ALIGN(0x8);
 .tmp : AT(LOADADDR(.bss) + SIZEOF(.bss))
 {
  KEEP(*(.qmem))
 } > sram

 _RISC32_DCACHE_SIZE = 8192;
 _RISC32_DCACHE_LINE_SIZE = 16;
 _RISC32_DCACHE_WAYS = 4;

    PROVIDE(_boot_stack = 0xB000C000);
    PROVIDE(_risc32_regbase = 0xA0201E00);
    PROVIDE(___qmem_addr = 0xB0000000);
}

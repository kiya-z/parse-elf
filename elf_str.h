
#define ELFMAG "\177ELF"

char str_e_ident_class[3][13] = {
  "ELFCLASSNONE",
  "ELFCLASS32",
  "ELFCLASS64"
};

char str_e_ident_data[3][12] = {
  "ELFDATANONE",
  "ELFDATA2LSB",
  "ELFDATA2MSB"
};

#define EV_CURRENT "1"

char str_e_type[7][10] = {
  "ET_NONE",
  "ET_REL",
  "ET_EXEC",
  "ET_DYN",
  "ET_CORE",
  "ET_LOPROC",
  "ET_HIPROC"
};

char str_e_machine[11][15] = {
  "EM_NONE",
  "EM_M32",
  "EM_SPARC",
  "EM_386",
  "EM_68K",
  "EM_88K",
  "EM_486",
  "EM_860",
  "EM_MIPS",
  "EM_MIPS_RS4_BE",
  "RESERVED"
};

char str_e_version[2][11] = {
  "EV_NONE",
  "EV_CURRENT"
};

char str_p_type[16][13] = {
  "NULL",
  "LOAD",
  "DYNAMIC",
  "INTERP",
  "NOTE",
  "SHLIB",
  "PHDR",
  "TLS",
  "LOOS",
  "HIOS",
  "LOPROC",
  "HIPROC",
  "GNU_EH_FRAME",
  "GNU_STACK",
  "EXIDX",
  "GNU_RELRO"
};

char str_p_flags[5][2] = {
  "",
  "E",
  "W",
  "",
  "R"
};


char str_sh_type[40][23] = {
  "NULL",
  "PROGBITS",
  "SYMTAB",
  "STRTAB",
  "RELA",
  "HASH",
  "DYNAMIC",
  "NOTE",
  "NOBITS",
  "REL",
  "SHLIB",
  "DYNSYM",
  "",
  "",
  "INIT_ARRAY",
  "FINI_ARRAY",
  "PREINIT_ARRAY",
  "GROUP",
  "SYMTAB_SHNDX",
  //19~22
  "GNU_INCREMENTAL_INPUTS",  //0x6fff4700,
  "GNU_INCREMENTAL_SYMTAB",  //0x6fff4701,
  "GNU_INCREMENTAL_RELOCS",  //0x6fff4702,
  "GNU_INCREMENTAL_GOT_PLT", //0x6fff4703,
  //23~32
  "GNU_ATTRIBUTES", //0x6ffffff5,
  "GNU_HASH",       //0x6ffffff6,
  "GNU_LIBLIST",    //0x6ffffff7,
    //26~29
  "HIPROC", //0x7fffffff,
  "HIUSER", //0xffffffff,
  "LOOS",   //0x60000000,
  "LOUSER", //0x80000000,

  "VERDEF",         //0x6ffffffd,
  "VERNEED",        //0x6ffffffe,
  "VERSYM",         //0x6fffffff,
  //33~39
  "SPARC_GOTDATA",      //0x70000000,
  "ARM_EXIDX",          //0x70000001,
  "ARM_PREEMPTMAP",     //0x70000002,
  "ARM_ATTRIBUTES",     //0x70000003,
  "ARM_DEBUGOVERLAY",   //0x70000004,
  "ARM_OVERLAYSECTION", //0x70000005,
  "MIPS_REGINFO",       //0x70000006,
};


char str_sh_flag[17] = "WAXMSILOGTmmoEm";

char sh_flag_tips[230] = "\nkey to flags:\nW(WRITE), A(ALLOC), X(EXECINSTR), M(MERGE), S(STRINGS),\
I(INFO_LINK), L(LINK_ORDER), O(OS_NONCONFORMING), G(GROUP), T(TLS), M(MASKOS),\
m(MASKPROC), o(ORDERED), E(EXCLUDE), m1(MIPS_GPREL), X(X86_64_LARGE)\n\n";

char str_section_header_index[3][4] = {
  "UND",
  "ABS",
  "COM"
};

char str_symbol_table_type[7][8] = {
  "NOTYPE",
  "OBJECT",
  "FUNC",
  "SECTION",
  "FILE",
  "COMMON",
  "TLS"
};

char str_symbol_table_bind[3][7] = {
  "LOCAL",
  "GLOBAL",
  "WEAK"
};

char str_relocation_type[46][24] = {
  "R_386_NONE", // 0,        // No reloc
  "R_386_32", // 1,          // Direct 32 bit zero extended
  "R_386_PC32", // 2,        // PC relative 32 bit signed
  "R_386_GOT32", // 3,       // 32 bit GOT entry
  "R_386_PLT32", // 4,       // 32 bit PLT address
  "R_386_COPY", // 5,        // Copy symbol at runtime
  "R_386_GLOB_DAT", // 6,    // Create GOT entry
  "R_386_JUMP_SLOT", // 7,   // Create PLT entry
  "R_386_RELATIVE", // 8,    // Adjust by program base
  "R_386_GOTOFF", // 9,      // 32-bit GOT offset
  "R_386_GOTPC", // 10,      // 32-bit PC relative offset to GOT
  // Used by Sun.
  "R_386_32PLT", // 11,
  // TLS extensions.
  "R_386_TLS_TPOFF", // 14,  // Outstanding Initial Exec reloc, gnu-style (both)
  "R_386_TLS_IE", // 15,     // Initial Initial Exec reloc, gnu-style (no-PIC)
  "R_386_TLS_GOTIE", // 16,  // Initial Initial Exec reloc, gnu-style (for PIC)
  "R_386_TLS_LE", // 17,     // Initial Local Exec reloc, gnu-style
  "R_386_TLS_GD", // 18,     // Initial General Dynamic reloc, gnu-style
  "R_386_TLS_LDM", // 19,    // Initial Local Dynamic reloc, gnu-style
  // GNU extensions.
  "R_386_16", // 20,         // Direct 16 bit zero extended
  "R_386_PC16", // 21,       // 16 bit sign extended pc relative
  "R_386_8", // 22,          // Direct 8 bit sign extended
  "R_386_PC8", // 23,        // 8 bit sign extended pc relative
  // More TLS relocs.
  "R_386_TLS_GD_32", // 24,     // Initial General Dynamic reloc, sun-style
  "R_386_TLS_GD_PUSH", // 25,   // Initial General Dynamic reloc, sun-style
  "R_386_TLS_GD_CALL", // 26,   // Initial General Dynamic reloc, sun-style
  "R_386_TLS_GD_POP", // 27,    // Initial General Dynamic reloc, sun-style
  "R_386_TLS_LDM_32", // 28,    // Initial Local Dynamic reloc, sun-style
  "R_386_TLS_LDM_PUSH", // 29,  // Initial Local Dynamic reloc, sun-style
  "R_386_TLS_LDM_CALL", // 30,  // Initial Local Dynamic reloc, sun-style
  "R_386_TLS_LDM_POP", // 31,   // Initial Local Dynamic reloc, sun-style
  "R_386_TLS_LDO_32", // 32,    // Initial Local Dynamic reloc, sun+gnu styles
  "R_386_TLS_IE_32", // 33,     // Initial Initial Exec reloc, sun-style
  "R_386_TLS_LE_32", // 34,     // Initial Local Exec reloc, sun-style
  "R_386_TLS_DTPMOD32", // 35,  // Outstanding General/Local Dynamic reloc, sun+gnu
  "R_386_TLS_DTPOFF32", // 36,  // Outstanding General Dynamic reloc, sun+gnu
  "R_386_TLS_TPOFF32", // 37,   // Outstanding Initial Exec reloc, sun-style
  "R_386_TLS_GOTDESC", // 39,   // GOT offset for TLS descriptor
  "R_386_TLS_DESC_CALL", // 40, // Marker of call through TLS desc for relaxation
  "R_386_TLS_DESC", // 41,      // TLS descriptor containing pointer to code and
                            // to argument, returning TLS offset for symbol
  "R_386_IRELATIVE", // 42,     // Adjust indirectly by program base
  // Used by Intel.
  "R_386_USED_BY_INTEL_200", // 200,
  // GNU vtable garbage collection extensions.
  "R_386_GNU_VTINHERIT", // 250,
  "R_386_GNU_VTENTRY", // 251
};

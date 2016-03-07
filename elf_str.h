
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

  "verdef",         //0x6ffffffd,
  "verneed",        //0x6ffffffe,
  "versym",         //0x6fffffff,
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

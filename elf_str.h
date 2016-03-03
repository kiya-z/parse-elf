
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

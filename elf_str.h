
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

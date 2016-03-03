#define EI_NIDENT 16

typedef struct ELFHEADER {
    unsigned char e_ident[EI_NIDENT];
    unsigned short e_type;
    unsigned short e_machine;
    unsigned short e_version;
    int e_entry;
    int e_phoff;
    int e_shoff;
    unsigned short e_flags;
    unsigned short e_ehsize;
    unsigned short e_phentsize;
    unsigned short e_phnum;
    unsigned short e_shentsize;
    unsigned short e_shnum;
    unsigned short e_shstrndx;
} ELFHEADER;

ELFHEADER header;

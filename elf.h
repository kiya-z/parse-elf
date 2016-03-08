typedef unsigned int Elf32_Addr;
typedef unsigned short Elf32_Half;
typedef unsigned int Elf32_Off;
typedef signed int Elf32_Sword;
typedef unsigned int Elf32_Word;

#define EI_NIDENT 16

typedef struct elf32_hdr{
 unsigned char e_ident[EI_NIDENT];
 Elf32_Half e_type;
 Elf32_Half e_machine;
 Elf32_Word e_version;
 Elf32_Addr e_entry;
 Elf32_Off e_phoff;
 Elf32_Off e_shoff;
 Elf32_Word e_flags;
 Elf32_Half e_ehsize;
 Elf32_Half e_phentsize;
 Elf32_Half e_phnum;
 Elf32_Half e_shentsize;
 Elf32_Half e_shnum;
 Elf32_Half e_shstrndx;
} Elf32_Ehdr;

Elf32_Ehdr header;

typedef struct elf32_phdr{
 Elf32_Word p_type;
 Elf32_Off  p_offset;
 Elf32_Addr p_vaddr;
 Elf32_Addr p_paddr;
 Elf32_Word p_filesz;
 Elf32_Word p_memsz;
 Elf32_Word p_flags;
 Elf32_Word p_align;
} Elf32_Phdr;

Elf32_Phdr program_Header[10];


typedef struct elf32_shdr {
 Elf32_Word sh_name;
 Elf32_Word sh_type;
 Elf32_Word sh_flags;
 Elf32_Addr sh_addr;
 Elf32_Off sh_offset;
 Elf32_Word sh_size;
 Elf32_Word sh_link;
 Elf32_Word sh_info;
 Elf32_Word sh_addralign;
 Elf32_Word sh_entsize;
} Elf32_Shdr;

Elf32_Shdr section_header[30];
char section_header_name[30][30];

typedef struct elf32_sym{
 Elf32_Word st_name;
 Elf32_Addr st_value;
 Elf32_Word st_size;
 unsigned char st_info;
 unsigned char st_other;
 Elf32_Half st_shndx;
} Elf32_Sym;

int symbols_offset[3];

//type:REL
typedef struct elf32_rel {
 Elf32_Addr r_offset;
 Elf32_Word r_info;
} Elf32_Rel;

//type:RELA
// typedef struct elf32_rela{
//  Elf32_Addr r_offset;
//  Elf32_Word r_info;
//  Elf32_Sword r_addend;
// } Elf32_Rela;

typedef struct elf32_note {
 Elf32_Word n_namesz;
 Elf32_Word n_descsz;
 Elf32_Word n_type;
} Elf32_Nhdr;

typedef struct dynamic{
 Elf32_Sword d_tag;
 union{
 Elf32_Sword d_val;
 Elf32_Addr d_ptr;
 } d_un;
} Elf32_Dyn;

// .got SHT_PROGBITS SHF_ALLOC + SHF_WRITE
// .hash SHT_HASH SHF_ALLOC
// .plt SHT_PROGBITS SHF_ALLOC + SHF_EXECINSTR

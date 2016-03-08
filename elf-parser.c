#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

#include"elf.h"
#include"elf_str.h"

#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

#define ELF32_R_SYM(x) ((x) >> 8)
#define ELF32_R_TYPE(x) ((x) & 0xff)

int shstrtab_offset = 0, strtab_offset = 0, dynstr_offset = 0;
int dynsym_ndx = 0;

void read_header(FILE* fp) {
  int i = 0;

  /******ident******/
  fread(header.e_ident,16,1,fp);
  if(header.e_ident[4] == 2){
    printf("不支持64位elf解析!\n");
    exit(1);
  }

  printf("\n文件头:\n");
  printf("    MAG:  %s\n    类别: %s\n", ELFMAG, str_e_ident_class[header.e_ident[4]]);
  printf("    编码: %s\n    版本: %s\n\n", str_e_ident_data[header.e_ident[5]], EV_CURRENT);

  /******type/machine/version******/
  unsigned short t1[3];
  fread(t1,2,2,fp);
  header.e_type = t1[0];
    if (header.e_type == 0xff00) printf("%s\n", str_e_type[5]);
    else if (header.e_type == 0xffff) printf("%s\n", str_e_type[6]);
    else printf("  文件类型:  %s\n", str_e_type[header.e_type]);
  header.e_machine = t1[1]; printf("  处理器:  %s\n", str_e_machine[header.e_machine > 10 ? 10 : header.e_machine]);

  /******version/entry/phoff/shoff******/
  int t2[6];
  fread(t2,4,5,fp);
  header.e_version = t2[0]; printf("  版本:  %s\n", str_e_version[header.e_version]);
  header.e_entry = t2[1];   printf(" >入口偏移: 0x%x\n", header.e_entry);
  header.e_phoff = t2[2];   printf(" >程序头偏移:  0x%x\n", header.e_phoff);
  header.e_shoff = t2[3];   printf(" >节头偏移: 0x%x\n", header.e_shoff);
  header.e_flags = t2[4];   printf("  标志: 0x%x\n\n", header.e_flags);

  /******ehsize/entry/phoff/shoff******/
  unsigned short t3[7];
  fread(t3,2,6,fp);
  header.e_ehsize = t3[0];    printf("  文件头大小:  0x%x\n", header.e_ehsize);
  header.e_phentsize = t3[1]; printf("  程序头单个表项大小:  0x%x\n", header.e_phentsize);
  header.e_phnum = t3[2];     printf("  程序头表项个数:  0x%x\n", header.e_phnum);
  header.e_shentsize = t3[3]; printf("  节头单个表项大小: 0x%x\n", header.e_shentsize);
  header.e_shnum = t3[4];     printf("  节头表项个数: 0x%x\n", header.e_shnum);
  header.e_shstrndx = t3[5];  printf("  节头表项名字索引: 0x%x\n", header.e_shstrndx);

  printf("\n******************************************************************\n\n");
}

void read_program_header(FILE* fp) {
  int i = 0, j = 0;
  int tmp[9];
  char interp[21];

  printf("程序头:\n");
  printf("   Type                 Offset     VirtAddr     PhysAddr      FileSiz   MemSiz    Flg   Align\n");

  fseek(fp,header.e_phoff,SEEK_SET);
  for(i = 0; i < header.e_phnum; i++){
    fread(tmp,4,8,fp);
    program_Header[i].p_type = tmp[0];
      if(program_Header[i].p_type == 0x60000000)       printf("   %-15s  ", str_p_type[8]);
      else if(program_Header[i].p_type == 0x6fffffff)  printf("   %-15s  ", str_p_type[9]);
      else if(program_Header[i].p_type == 0x70000000)  printf("   %-15s  ", str_p_type[10]);
      else if(program_Header[i].p_type == 0x7fffffff)  printf("   %-15s  ", str_p_type[11]);
      else if(program_Header[i].p_type == 0x6474e550)  printf("   %-15s  ", str_p_type[12]);
      else if(program_Header[i].p_type == (0x60000000 + 0x474e551))  printf("   %-15s  ", str_p_type[13]);
      else if(program_Header[i].p_type == 0x70000001)  printf("   %-15s  ", str_p_type[14]);
      else if(program_Header[i].p_type == 0x6474e552)  printf("   %-15s  ", str_p_type[15]);
      else printf("   %-15s  ", str_p_type[program_Header[i].p_type]);

    program_Header[i].p_offset = tmp[1];   printf(" 0x%08x ", program_Header[i].p_offset);
    program_Header[i].p_vaddr = tmp[2];    printf(" 0x%08x  ", program_Header[i].p_vaddr);
    program_Header[i].p_paddr = tmp[3];    printf(" 0x%08x  ", program_Header[i].p_paddr);
    program_Header[i].p_filesz = tmp[4];   printf(" 0x%08x ", program_Header[i].p_filesz);
    program_Header[i].p_memsz = tmp[5];    printf(" 0x%08x  ", program_Header[i].p_memsz);
    program_Header[i].p_flags = tmp[6];
      if((program_Header[i].p_flags & 0x4) != 0)  printf("%s", str_p_flags[4]); else printf(" ");
      if((program_Header[i].p_flags & 0x2) != 0)  printf("%s", str_p_flags[2]); else printf(" ");
      if((program_Header[i].p_flags & 0x1) != 0)  printf("%s", str_p_flags[1]); else printf(" ");
      printf("  ");
    program_Header[i].p_align = tmp[7];    printf(" 0x%x\n", program_Header[i].p_align);

    if(program_Header[i].p_type == 3){
      long cur_pos = ftell(fp);
      fseek(fp,program_Header[i].p_offset,SEEK_SET);
      fread(interp,20,1,fp);
      fseek(fp,cur_pos,SEEK_SET);
      printf("    %s\n", interp);
    }
  }
  printf("\n******************************************************************\n\n");

}

void read_segment_header(FILE* fp) {
  int i = 0, shstrtab_offset = 0;
  int tmp[11];

  printf("节头:\n");
  printf("  [Nr] Name                       Type                 Addr      Off       Size    ES   Flg Lk  Inf Al\n");

  fseek(fp,header.e_shoff,SEEK_SET);
  for(i = 0; i < header.e_shnum; i++){
    fread(tmp,4,10,fp);
    section_header[i].sh_name = tmp[0];
    section_header[i].sh_type = tmp[1];
    section_header[i].sh_addr = tmp[3];
    section_header[i].sh_offset = tmp[4];
    section_header[i].sh_size = tmp[5];
    section_header[i].sh_entsize = tmp[9];
    section_header[i].sh_flags = tmp[2];
    section_header[i].sh_link = tmp[6];
    section_header[i].sh_info = tmp[7];
    section_header[i].sh_addralign = tmp[8];

    if (section_header[i].sh_type == 0x3) {
      long cur_pos = ftell(fp);
      char tmp_name[31];

      fseek(fp,section_header[i].sh_offset+section_header[i].sh_name,SEEK_SET); fread(tmp_name,30,1,fp);
      if(strcmp(tmp_name,".shstrtab") == 0) shstrtab_offset = section_header[i].sh_offset;
      fseek(fp,cur_pos,SEEK_SET);
    }
  }

  long cur_pos = ftell(fp);
  for(i = 0; i < header.e_shnum; i++){
    char tmp_name[31];
    fseek(fp,shstrtab_offset+section_header[i].sh_name,SEEK_SET);
    fread(section_header_name[i],30,1,fp);
    if(strcmp(section_header_name[i],".dynstr") == 0)  dynstr_offset = section_header[i].sh_offset;
    else if(strcmp(section_header_name[i],".strtab") == 0)   strtab_offset = section_header[i].sh_offset;
  }
  fseek(fp,cur_pos,SEEK_SET);

  for(i = 0; i < header.e_shnum; i++){
    printf("  [%2d]  ", i);
    printf("%-25s ", section_header_name[i]);

    if(section_header[i].sh_type < 0x19)   printf("%-15s  ", str_sh_type[section_header[i].sh_type]);
    else{
      int sev_bit = section_header[i].sh_type & 0xfffffff0;
      int last = section_header[i].sh_type & 0xf;

      switch (sev_bit) {
        case 0x6fff4700:  printf("%-15s  ", str_sh_type[19+last]);  break;
        case 0x6ffffff0:  printf("%-15s  ", str_sh_type[17+last]);  break;
        case 0x70000000:  printf("%-15s  ", str_sh_type[33+last]);  break;
        case 0x7ffffff0:  printf("%-15s  ", str_sh_type[26]);  break;
        case 0xfffffff0:  printf("%-15s  ", str_sh_type[27]);  break;
        case 0x60000000:  printf("%-15s  ", str_sh_type[28]);  break;
        case 0x80000000:  printf("%-15s  ", str_sh_type[29]);  break;
      }
    }

    printf("0x%08x  ", section_header[i].sh_addr);
    printf("0x%06x  ", section_header[i].sh_offset);
    printf("0x%06x  ", section_header[i].sh_size);
    printf("%02x  ", section_header[i].sh_entsize);

    char flags[4] = "";
    int j = 0;
    if((section_header[i].sh_flags & 0x1) != 0)         flags[j++] = str_sh_flag[0];
    if((section_header[i].sh_flags & 0x2) != 0)         flags[j++] = str_sh_flag[1];
    if((section_header[i].sh_flags & 0x4) != 0)         flags[j++] = str_sh_flag[2];
    if((section_header[i].sh_flags & 0x10) != 0)        flags[j++] = str_sh_flag[3];
    if((section_header[i].sh_flags & 0x20) != 0)        flags[j++] = str_sh_flag[4];
    if((section_header[i].sh_flags & 0x40) != 0)        flags[j++] = str_sh_flag[5];
    if((section_header[i].sh_flags & 0x80) != 0)        flags[j++] = str_sh_flag[6];
    if((section_header[i].sh_flags & 0x100) != 0)       flags[j++] = str_sh_flag[7];
    if((section_header[i].sh_flags & 0x200) != 0)       flags[j++] = str_sh_flag[8];
    if((section_header[i].sh_flags & 0x400) != 0)       flags[j++] = str_sh_flag[9];
    if((section_header[i].sh_flags & 0x0ff00000) != 0)  flags[j++] = str_sh_flag[10];
    if((section_header[i].sh_flags & 0xf0000000) != 0)  flags[j++] = str_sh_flag[11];
    if((section_header[i].sh_flags & 0x40000000) != 0)  flags[j++] = str_sh_flag[12];
    if((section_header[i].sh_flags & 0x80000000) != 0)  flags[j++] = str_sh_flag[13];
    if((section_header[i].sh_flags & 0x10000000) != 0)  flags[j++] = str_sh_flag[14];
    printf("%3s  ",flags);

    printf("%2d  ", section_header[i].sh_link);
    printf("%2d  ", section_header[i].sh_info);
    printf("%2d  \n", section_header[i].sh_addralign);
  }

  printf("%s",sh_flag_tips);

  printf("\n******************************************************************\n\n");

}

void get_section_segment_mapping() {
  int i = 0, j = 0;
  printf("段节对应关系:\n");
  for(i = 0; i < header.e_phnum; i++){
    unsigned int start_addr = program_Header[i].p_offset;
    unsigned int end_addr = start_addr + program_Header[i].p_filesz;
    printf("  %02d   ", i);
    for(j = 1; j < header.e_shnum; j++){
      if (section_header[j].sh_offset >= start_addr && section_header[j].sh_offset < end_addr) {
        printf("%s  ", section_header_name[j]);
      }
    }
    printf("\n");
  }
  printf("\n******************************************************************\n\n");

}

void read_symbol(FILE* fp) {
  int i = 0,j = 0;
  for(i = 0 ;i < header.e_shnum; i++){
    if(section_header[i].sh_type == 2 || section_header[i].sh_type == 11){
      printf("\nSymbols of '%s':\n",section_header_name[i]);
      printf("   Num:    Value  Size Type     Bind     Ndx  Name\n");

      int num = section_header[i].sh_size / section_header[i].sh_entsize;
      char buffer[0x10];
      int name_tab_offset = 0;
      char name[31];
      if(section_header[i].sh_type == 2) {
        dynsym_ndx = i;
        name_tab_offset = strtab_offset;
      } else name_tab_offset = dynstr_offset;

      for(j = 0; j < num; j++){
        fseek(fp,section_header[i].sh_offset+j*section_header[i].sh_entsize,SEEK_SET);
        fread(buffer,section_header[i].sh_entsize,1,fp);
        Elf32_Sym* sym_tmp = (Elf32_Sym*)buffer;
        printf("    %2d:  %08x  %3d ", j,sym_tmp->st_value,sym_tmp->st_size);

        char bind = ELF32_ST_BIND(sym_tmp->st_info);
        char type = ELF32_ST_TYPE(sym_tmp->st_info);
        // char info = ELF32_ST_INFO(bind,type);

        printf("%-7s  %-7s  ", str_symbol_table_type[type],str_symbol_table_bind[bind]);
        // printf("%d   ", info);

        switch (sym_tmp->st_shndx) {
          case 0x0:    printf("%3s  ", str_section_header_index[0]); break;
          case 0xfff1: printf("%3s  ", str_section_header_index[1]); break;
          case 0xfff2: printf("%3s  ", str_section_header_index[2]); break;
          default:     printf("%3d  ", sym_tmp->st_shndx);
          // default:     printf("%-30s  ", section_header_name[sym_tmp->st_shndx]);
        }

        fseek(fp,name_tab_offset+sym_tmp->st_name,SEEK_SET);
        fread(name,30,1,fp);
        printf("%-30s", name);
        printf("\n");
      }
    }
  }
  printf("\n******************************************************************\n\n");

}

void read_relocation(FILE *fp){
  int i = 0,j = 0;
  for(i = 0; i < header.e_shnum; i++){
    if(section_header[i].sh_type == 0x9){
      int rel_num = section_header[i].sh_size / section_header[i].sh_entsize;
      printf("重定位节 '%s' 位于偏移量 0x%x 含有 %d 个条目:\n", section_header_name[i],section_header[i].sh_offset,rel_num);
      printf(" Offset     Info    Type            Sym.Value  Sym. Name\n");

      for(j = 0 ; j < rel_num; j++){
        unsigned int rel_tmp[8];
        fseek(fp,section_header[i].sh_offset+j*section_header[i].sh_entsize,SEEK_SET);
        fread(rel_tmp,8,1,fp);
        Elf32_Rel* rel = (Elf32_Rel*)rel_tmp;
        char sym = ELF32_R_SYM(rel->r_info);
        char type = ELF32_R_TYPE(rel->r_info);

        printf("%08x  %08x  ", rel->r_offset, rel->r_info);
        if(type == 200) printf("%s  ", str_relocation_type[43]);
        if(type == 250) printf("%s  ", str_relocation_type[44]);
        if(type == 251) printf("%s  ", str_relocation_type[45]);
        else printf("%s  ", str_relocation_type[type]);

        //跳到dynstr_tab读取索引为sym的一项，取出value和name
        char buffer[0x10], name[31];
        fseek(fp,section_header[dynsym_ndx].sh_offset+sym*section_header[dynsym_ndx].sh_entsize,SEEK_SET);
        printf("%lx ", ftell(fp));
        fread(buffer,section_header[dynsym_ndx].sh_entsize,1,fp);
        printf("%s  ", buffer);
        Elf32_Sym* sym_tmp = (Elf32_Sym*)buffer;
        fseek(fp,dynstr_offset+sym_tmp->st_name,SEEK_SET);
        printf("%x %x %lx ",dynstr_offset, sym_tmp->st_name,ftell(fp));
        fread(name,30,1,fp);
        printf("%8x %s\n", sym_tmp->st_value, name);
      }
      printf("\n");
    }
  }
  printf("\n******************************************************************\n\n");
}

void press_to_continue() {
  // char ch = getchar();
  // if(ch != '\n') exit(1);
}

void read_it(FILE* fp){
  read_header(fp);
  press_to_continue();

  read_program_header(fp);
  press_to_continue();

  read_segment_header(fp);
  press_to_continue();

  get_section_segment_mapping();
  press_to_continue();

  read_symbol(fp);
  press_to_continue();

  read_relocation(fp);
}

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    printf("[usage] elf-parser elf-file-name\n");
    exit(1);
  }
  printf("\n>>>>>>>>>>>>>>>>>>  \"%s\"  <<<<<<<<<<<<<<<<<<<<<\n",argv[1]);
  FILE *fp;
  fp = fopen(argv[1], "rb+");
  if (fp == NULL) {
    printf("file doesn't exists!\n");
    exit(1);
  }
  read_it(fp);
  fclose(fp);
  return 0;
}

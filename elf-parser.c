#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

#include"elf.h"
#include"elf_str.h"

void read_header(FILE* fp) {
  int i = 0;
  printf("\n文件头:\n");

  /******ident******/
  fread(header.e_ident,16,1,fp);
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

  printf("\n");
}

void read_program_header(FILE* fp) {
  int i = 0, j = 0;
  int tmp[9];
  char interp[21];

  printf("程序头:\n");
  printf("   Type            Offset     VirtAddr     PhysAddr      FileSiz   MemSiz    Flg   Align\n");

  fseek(fp,header.e_phoff,SEEK_SET);
  for(i = 0; i < header.e_phnum; i++){
    fread(tmp,4,8,fp);
    program_Header[i].p_type = tmp[0];
      if(program_Header[i].p_type == 0x60000000)       printf("   %-10s  ", str_p_type[8]);
      else if(program_Header[i].p_type == 0x6fffffff)  printf("   %-10s  ", str_p_type[9]);
      else if(program_Header[i].p_type == 0x70000000)  printf("   %-10s  ", str_p_type[10]);
      else if(program_Header[i].p_type == 0x7fffffff)  printf("   %-10s  ", str_p_type[11]);
      else if(program_Header[i].p_type == 0x6474e550)  printf("   %-10s  ", str_p_type[12]);
      else if(program_Header[i].p_type == (0x60000000 + 0x474e551))  printf("   %-10s  ", str_p_type[13]);
      else if(program_Header[i].p_type == 0x70000001)  printf("   %-10s  ", str_p_type[14]);
      else if(program_Header[i].p_type == 0x6474e552)  printf("   %-10s  ", str_p_type[15]);
      else printf("   %-10s  ", str_p_type[program_Header[i].p_type]);

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

    if(program_Header[i].p_type == 3 || program_Header[i].p_type == 4){
      long cur_pos = ftell(fp);
      fseek(fp,program_Header[i].p_offset,SEEK_SET);
      fread(interp,20,1,fp);
      printf("    %s\n", interp);
      fseek(fp,cur_pos,SEEK_SET);
    }
  }
  printf("\n");
}

void read_segment_header(FILE* fp) {
  int i = 0;
  int tmp[11];

  printf("节头:\n");
  printf("  [Nr] Name              Type                 Addr      Off       Size    ES  Flg Lk Inf Al\n");

  fseek(fp,header.e_shoff,SEEK_SET);
  for(i = 0; i < header.e_shnum; i++){
    fread(tmp,4,10,fp);

    printf("  [%2d]  ", i);
    segment_header[i].sh_name = tmp[0];       printf("%-15x  ", segment_header[i].sh_name);
    segment_header[i].sh_type = tmp[1];
      switch (segment_header[i].sh_type) {
        case 0x70000000:  printf("%-15s  ", str_sh_type[19]);  break;
        case 0x7fffffff:  printf("%-15s  ", str_sh_type[20]);  break;
        case 0x80000000:  printf("%-15s  ", str_sh_type[21]);  break;
        case 0xffffffff:  printf("%-15s  ", str_sh_type[22]);  break;
        case 0x70000001:  printf("%-15s  ", str_sh_type[23]);  break;
        case 0x70000003:  printf("%-15s  ", str_sh_type[24]);  break;
        default:          printf("%-15s  ", str_sh_type[segment_header[i].sh_type]);  break;
      }

    segment_header[i].sh_addr = tmp[3];       printf("0x%08x  ", segment_header[i].sh_addr);
    segment_header[i].sh_offset = tmp[4];     printf("0x%06x  ", segment_header[i].sh_offset);
    segment_header[i].sh_size = tmp[5];       printf("0x%06x  ", segment_header[i].sh_size);
    segment_header[i].sh_entsize = tmp[9];    printf("%02x  ", segment_header[i].sh_entsize);
    segment_header[i].sh_flags = tmp[2];
        char flags[4] = "";
        int j = 0;
        if((segment_header[i].sh_flags & 0x1) != 0)         flags[j++] = str_sh_flag[0];
        if((segment_header[i].sh_flags & 0x2) != 0)         flags[j++] = str_sh_flag[1];
        if((segment_header[i].sh_flags & 0x4) != 0)         flags[j++] = str_sh_flag[2];
        if((segment_header[i].sh_flags & 0x10) != 0)        flags[j++] = str_sh_flag[3];
        if((segment_header[i].sh_flags & 0x20) != 0)        flags[j++] = str_sh_flag[4];
        if((segment_header[i].sh_flags & 0x40) != 0)        flags[j++] = str_sh_flag[5];
        if((segment_header[i].sh_flags & 0x80) != 0)        flags[j++] = str_sh_flag[6];
        if((segment_header[i].sh_flags & 0x100) != 0)       flags[j++] = str_sh_flag[7];
        if((segment_header[i].sh_flags & 0x200) != 0)       flags[j++] = str_sh_flag[8];
        if((segment_header[i].sh_flags & 0x400) != 0)       flags[j++] = str_sh_flag[9];
        if((segment_header[i].sh_flags & 0x0ff00000) != 0)  flags[j++] = str_sh_flag[10];
        if((segment_header[i].sh_flags & 0xf0000000) != 0)  flags[j++] = str_sh_flag[11];
        if((segment_header[i].sh_flags & 0x40000000) != 0)  flags[j++] = str_sh_flag[12];
        if((segment_header[i].sh_flags & 0x80000000) != 0)  flags[j++] = str_sh_flag[13];
        if((segment_header[i].sh_flags & 0x10000000) != 0)  flags[j++] = str_sh_flag[14];
        printf("%3s  ",flags);

    segment_header[i].sh_link = tmp[6];       printf("%x  ", segment_header[i].sh_link);
    segment_header[i].sh_info = tmp[7];       printf("%x  ", segment_header[i].sh_info);
    segment_header[i].sh_addralign = tmp[8];  printf("%x  \n", segment_header[i].sh_addralign);

  }

  printf("%s",sh_flag_tips);

}

void read_it(FILE* fp){
  read_header(fp);
  read_program_header(fp);
  read_segment_header(fp);
}

int main(int argc, char const *argv[]) {
  FILE *fp;
  fp = fopen("/home/kiya/myspace/parse-elf/libmobisec.so", "rb+");
  if (fp == NULL) {
    printf("file doesn't exists!\n");
  }
  read_it(fp);
  fclose(fp);
  return 0;
}

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

#include"elf.h"
#include"elf_str.h"

void read_header(FILE* fp) {
  int i = 0;

  /******ident******/
  fread(header.e_ident,16,1,fp);
  printf("    MAG:  %s\n", ELFMAG);
  printf("    类别: %s\n", str_e_ident_class[header.e_ident[4]]);
  printf("    编码: %s\n", str_e_ident_data[header.e_ident[5]]);
  printf("    版本: %s\n\n", EV_CURRENT);

  /******type/machine/version******/
  unsigned short tmp[4];
  fread(tmp,2,3,fp);

  header.e_type = tmp[0];
  if (header.e_type == 0xff00) printf("%s\n", str_e_type[5]);
  else if (header.e_type == 0xffff) printf("%s\n", str_e_type[6]);
  else printf("文件类型:  %s\n", str_e_type[header.e_type]);

  header.e_machine = tmp[1];
  printf("处理器:  %s\n", str_e_machine[header.e_machine > 10 ? 10 : header.e_machine]);

  header.e_version = tmp[2];
  printf("版本:  %s\n", str_e_version[header.e_version]);

}



int main(int argc, char const *argv[]) {
  FILE *fp;

  fp = fopen("/home/kiya/myspace/parse-elf/libmobisec.so", "rb+");
  if (fp == NULL) {
    printf("file doesn't exists!\n");
  }
  read_header(fp);

  fclose(fp);
  return 0;
}

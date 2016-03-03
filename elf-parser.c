#include<stdio.h>
#include<fcntl.h>

#include"elf.h"
#include"elf_str.h"

void read_header(FILE* fp) {
  int i = 0;
  unsigned char buffer[20];

  fread(buffer,16,1,fp);
  for (i = 0; i < 16; i++) {
    header.e_ident[i] = buffer[i];
    switch (i) {
      case 0: printf("    MAG:  %s\n", ELFMAG); break;
      case 4: printf("    类别: %s\n", str_e_ident_class[header.e_ident[i]]); break;
      case 5: printf("    编码: %s\n", str_e_ident_data[header.e_ident[i]]); break;
      case 6: printf("    版本: %s\n", EV_CURRENT);  break;
    }
  }
  printf("\n");
}



int main(int argc, char const *argv[]) {
  FILE *fp;

  fp = fopen("/home/kiya/myspace/parse-elf/libmobisec.so", "r");
  if (fp == NULL) {
    printf("file doesn't exists!\n");
  }
  read_header(fp);

  fclose(fp);
  return 0;
}

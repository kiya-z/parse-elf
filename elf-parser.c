#include<stdio.h>
#include<fcntl.h>

#include"elf.h"

int main(int argc, char const *argv[]) {
  FILE *fp;
  int i = 0;
  ElfHeader header;

  fp = fopen("/home/kiya/myspace/parse-elf/libmobisec.so", "r");
  if (fp == NULL) {
    printf("file doesn't exists!\n");
  }
  unsigned char buffer[20];
  fread(buffer,16,1,fp);

  for (i = 0; i < 16; i++) {
    header.e_ident[i] = buffer[i];
  }
  
  printf("HEADER:  ");
  for (i = 0; i < 16; i++) {
    printf("%02x ", header.e_ident[i]);
  }
  printf("\n");
  fclose(fp);
  return 0;
}

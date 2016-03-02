#include<stdio.h>
#include<fcntl.h>

int main(int argc, char const *argv[]) {
  FILE *fp;
  fp = fopen("/home/kiya/myspace/parse-elf/libmobisec.so", "r");
  if (fp == NULL) {
    printf("file doesn't exists!\n");
  }
  char buffer[20];
  fread(buffer,16,1,fp);
  int i = 0;
  for (i = 0; i < 16; i++) {
    printf("%02x ", buffer[i]);
  }
  printf("\n");
  fclose(fp);
  return 0;
}

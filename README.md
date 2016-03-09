## simplest elf parser

### hello world
```
>>>>>>>>>>>>>>>>>>  "test_files/ndk-hello"  <<<<<<<<<<<<<<<<<<<<<

文件头:
    MAG: ELF
    类别: ELFCLASS32
    编码: ELFDATA2LSB
    版本: 1

  文件类型:  ET_EXEC
  处理器:  RESERVED
  版本:  EV_CURRENT
 >入口偏移: 0x8274
 >程序头偏移:  0x34
 >节头偏移: 0x1494
  标志: 0x5000000

  文件头大小:  0x34
  程序头单个表项大小:  0x20
  程序头表项个数:  0x7
  节头单个表项大小: 0x28
  节头表项个数: 0x17
  节头表项名字索引: 0x16

******************************************************************

程序头:
   Type                 Offset     VirtAddr     PhysAddr      FileSiz   MemSiz    Flg   Align
   PHDR              0x00000034  0x00008034   0x00008034   0x000000e0  0x000000e0  R     0x4
   INTERP            0x00000114  0x00008114   0x00008114   0x00000013  0x00000013  R     0x1
    /system/bin/linker
   LOAD              0x00000000  0x00008000   0x00008000   0x00000370  0x00000370  R E   0x1000
   LOAD              0x00000ee4  0x00009ee4   0x00009ee4   0x0000011c  0x00000120  RW    0x1000
   DYNAMIC           0x00000f04  0x00009f04   0x00009f04   0x000000d0  0x000000d0  RW    0x4
   GNU_STACK         0x00000000  0x00000000   0x00000000   0x00000000  0x00000000  RW    0x0
   GNU_RELRO         0x00000ee4  0x00009ee4   0x00009ee4   0x0000011c  0x0000011c  RW    0x4

******************************************************************

节头:
  [Nr] Name                       Type                 Addr      Off       Size    ES   Flg Lk  Inf Al
  [ 0]                            NULL             0x00000000  0x000000  0x000000  00        0   0   0  
  [ 1]  .interp                   PROGBITS         0x00008114  0x000114  0x000013  00    A   0   0   1  
  [ 2]  .dynsym                   DYNSYM           0x00008128  0x000128  0x000070  10    A   3   1   4  
  [ 3]  .dynstr                   STRTAB           0x00008198  0x000198  0x000048  00    A   0   0   1  
  [ 4]  .hash                     HASH             0x000081e0  0x0001e0  0x000030  04    A   2   0   4  
  [ 5]  .rel.plt                  REL              0x00008210  0x000210  0x000018  08    A   2   0   4  
  [ 6]  .plt                      PROGBITS         0x00008228  0x000228  0x000038  00   AX   0   0   4  
  [ 7]  .text                     PROGBITS         0x00008260  0x000260  0x0000e8  00   AX   0   0   4  
  [ 8]  .note.android.ident       PROGBITS         0x00008348  0x000348  0x000018  00    A   0   0   4  
  [ 9]  .rodata                   PROGBITS         0x00008360  0x000360  0x000010  00    A   0   0   4  
  [10]  .fini_array               FINI_ARRAY       0x00009ee4  0x000ee4  0x000008  00   WA   0   0   4  
  [11]  .init_array               INIT_ARRAY       0x00009eec  0x000eec  0x000010  00   WA   0   0   4  
  [12]  .preinit_array            PREINIT_ARRAY    0x00009efc  0x000efc  0x000008  00   WA   0   0   4  
  [13]  .dynamic                  DYNAMIC          0x00009f04  0x000f04  0x0000d0  08   WA   3   0   4  
  [14]  .got                      PROGBITS         0x00009fd4  0x000fd4  0x00002c  00   WA   0   0   4  
  [15]  .data                     PROGBITS         0x0000a000  0x001000  0x000000  00   WA   0   0   1  
  [16]  .bss                      NOBITS           0x0000a000  0x001000  0x000004  00   WA   0   0   4  
  [17]  .comment                  PROGBITS         0x00000000  0x001000  0x000035  01   MS   0   0   1  
  [18]  .note.gnu.gold-version    NOTE             0x00000000  0x001038  0x00001c  00        0   0   4  
  [19]  .ARM.attributes           ARM_ATTRIBUTES   0x00000000  0x001054  0x00002b  00        0   0   1  
  [20]  .symtab                   SYMTAB           0x00000000  0x001080  0x000240  10       21  25   4  
  [21]  .strtab                   STRTAB           0x00000000  0x0012c0  0x000100  00        0   0   1  
  [22]  .shstrtab                 STRTAB           0x00000000  0x0013c0  0x0000d4  00        0   0   1  

key to flags:
W(WRITE), A(ALLOC), X(EXECINSTR), M(MERGE), S(STRINGS),I(INFO_LINK), L(LINK_ORDER), O(OS_NONCONFORMING), G(GROUP), T(TLS), M(MASKOS),m(MASKPROC), o(ORDERED), E(EXCLUDE), m1(MIPS_GPREL), X(X86_64_LARGE)


******************************************************************

段节对应关系:
  00   
  01   .interp  
  02   .interp  .dynsym  .dynstr  .hash  .rel.plt  .plt  .text  .note.android.ident  .rodata  
  03   .fini_array  .init_array  .preinit_array  .dynamic  .got  
  04   .dynamic  
  05   
  06   .fini_array  .init_array  .preinit_array  .dynamic  .got  

******************************************************************


Symbols of '.dynsym':
   Num:    Value  Size Type     Bind     Ndx  Name
     0:  00000000     0 NOTYPE   LOCAL    UND                                
     1:  00000000     0 FUNC     GLOBAL   UND  __libc_init                   
     2:  00000000     0 FUNC     GLOBAL   UND  __cxa_atexit                  
     3:  00000000     0 FUNC     GLOBAL   UND  puts                          
     4:  0000a000     0 NOTYPE   GLOBAL   ABS  _edata                        
     5:  0000a000     0 NOTYPE   GLOBAL   ABS  __bss_start                   
     6:  0000a004     0 NOTYPE   GLOBAL   ABS  _end                          

Symbols of '.symtab':
   Num:    Value  Size Type     Bind     Ndx  Name
     0:  00000000     0 NOTYPE   LOCAL    UND                                
     1:  00000000     0 FILE     LOCAL    ABS  crtbegin_dynamic.c            
     2:  00008260     0 NOTYPE   LOCAL      7  $a                            
     3:  000082d8     0 NOTYPE   LOCAL      7  $d                            
     4:  000082f0     0 NOTYPE   LOCAL      7  $a                            
     5:  00008308     0 NOTYPE   LOCAL      7  $d                            
     6:  00009ee4     0 NOTYPE   LOCAL     10  $d                            
     7:  00009eec     0 NOTYPE   LOCAL     11  $d                            
     8:  0000a000     0 NOTYPE   LOCAL     16  $d                            
     9:  00009efc     0 NOTYPE   LOCAL     12  $d                            
    10:  00009ef4     0 NOTYPE   LOCAL     11  $d                            
    11:  00000000     0 FILE     LOCAL    ABS  crtbrand.c                    
    12:  00008348     0 NOTYPE   LOCAL      8  $d                            
    13:  00008348    24 OBJECT   LOCAL      8  abitag                        
    14:  00000000     0 FILE     LOCAL    ABS  hello.c                       
    15:  00008360     0 NOTYPE   LOCAL      9  $d                            
    16:  00008310     0 NOTYPE   LOCAL      7  $a                            
    17:  00008344     0 NOTYPE   LOCAL      7  $d                            
    18:  00008260    20 FUNC     LOCAL      7  __atexit_handler_wrapper      
    19:  00008274   124 FUNC     LOCAL      7  _start                        
    20:  000082f0    32 FUNC     LOCAL      7  atexit                        
    21:  0000a000     4 OBJECT   LOCAL     16  __dso_handle                  
    22:  00009f04   208 OBJECT   LOCAL     13  _DYNAMIC                      
    23:  00009fe8     0 OBJECT   LOCAL     14  _GLOBAL_OFFSET_TABLE_         
    24:  00008228     0 NOTYPE   LOCAL      6  $a                            
    25:  00000000     0 FUNC     GLOBAL   UND  __libc_init                   
    26:  00009efc     4 OBJECT   GLOBAL    12  __PREINIT_ARRAY__             
    27:  00009eec     4 OBJECT   GLOBAL    11  __INIT_ARRAY__                
    28:  00009ee4     4 OBJECT   GLOBAL    10  __FINI_ARRAY__                
    29:  00009ef4     4 OBJECT   GLOBAL    11  __CTOR_LIST__                 
    30:  00008310    56 FUNC     GLOBAL     7  main                          
    31:  00000000     0 FUNC     GLOBAL   UND  __cxa_atexit                  
    32:  00000000     0 FUNC     GLOBAL   UND  puts                          
    33:  0000a000     0 NOTYPE   GLOBAL   ABS  _edata                        
    34:  0000a000     0 NOTYPE   GLOBAL   ABS  __bss_start                   
    35:  0000a004     0 NOTYPE   GLOBAL   ABS  _end                          

******************************************************************

重定位节 '.rel.plt' 位于偏移量 0x210 含有 3 个条目:
 Offset     Info    Type                    Sym.Value  Sym. Name
00009ff4  00000116  R_ARM_JUMP_SLOT          00000000  __libc_init
00009ff8  00000216  R_ARM_JUMP_SLOT          00000000  __cxa_atexit
00009ffc  00000316  R_ARM_JUMP_SLOT          00000000  puts


******************************************************************

Dynamic section at offset 0xf04:
 index    标记      类型                 地址/值
  00    00000003    PLTGOT              0x9fe8    
  01    00000002    PLTRELS             24 (bytes)
  02    00000017    JMPREL              0x8210    
  03    00000014    PLTREL              REL
  04    00000015    DEBUG               0x0       
  05    00000006    SYMTAB              0x8128    
  06    0000000b    SYMENT              16 (bytes)
  07    00000005    STRTAB              0x8198    
  08    0000000a    STRSZ               72 (bytes)
  09    00000004    HASH                0x81e0    
  10    00000001    NEEDED              共享库：[libc.so]
  11    00000001    NEEDED              共享库：[libdl.so]
  12    0000001a    FINI_ARRAY          0x9ee4    
  13    0000001c    FINI_ARRAYSZ        8 (bytes)
  14    00000019    INIT_ARRAY          0x9eec    
  15    0000001b    INIT_ARRAYSZ        16 (bytes)
  16    00000020    PREINIT_ARRAY       0x9efc    
  17    00000021    PREINIT_ARRAYSZ     8 (bytes)
  18    0000001e    FLAGS               BIND_NOW
  19    6ffffffb    FLAGS_1             NOW
  20    00000000    NULL                0x0       

******************************************************************

Displaying notes(.note.gnu.gold-version) found at file offset 0x00001038 with length 0x0000001c:
  Owner                       Data size	     Description
  GNU                         0x00000009     GNU_GOLD_VERSION
    Version: gold 1.11


******************************************************************
```

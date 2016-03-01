#!/usr/bin/python
# -*- coding: UTF-8 -*-

from utils import read_file

if __name__ == '__main__':
    # with open(r"/home/nagain/kiya/parse-elf/libmobisec.so",'rb') as f:
    #     print f.read(52)
    print read_file(r"/home/nagain/kiya/parse-elf/libmobisec.so",52)

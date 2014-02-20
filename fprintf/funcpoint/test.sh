#!/bin/sh
#yum install valgrind
gcc valgrind.c
valgrind --leak-check=full ./a.out
rm a.out
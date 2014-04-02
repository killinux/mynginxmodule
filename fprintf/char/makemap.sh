#!/bin/sh
#CFLAGS   =  -g -Wall -Wl,-Map,my.map？
gcc -o helloworld char_test.c -Wl,-Map,helloworld.map

#!/bin/sh
gcc -g -finstrument-functions includefunction.c test.c instrument.c -o test

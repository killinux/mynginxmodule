gcc instrument-funcition-test.c  -finstrument-fuctions -o hello
addr2line 0x40063e -e  hello -f
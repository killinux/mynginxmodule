#!/bin/sh
gcc testptread.c -lpthread -o testpthread
gcc testptread_lock.c -lpthread -o testpthread_lock


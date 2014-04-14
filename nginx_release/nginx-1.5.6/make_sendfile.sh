#!/bin/sh
rm -rf /usr/local/nginx_sendfile
make clean
./configure --prefix=/usr/local/nginx_sendfile --add-module=/data/haoning/mygit/mynginxmodule/mynginx/source/chapter3/sendfile
cp -f /data/haoning/mygit/mynginxmodule/nginx_release/debug/Makefile objs/
# --with-debug
#make  CFLAGS="-ggdb3 -O0"
make 
make install

#!/bin/sh
rm -rf /usr/local/nginx_sendfile
make clean
./configure --prefix=/usr/local/nginx_sendfile --add-module=/data/haoning/mygit/mynginxmodule/mynginx/source/chapter3/sendfile
# --with-debug
make  CFLAGS="-ggdb3 -O0"
make install

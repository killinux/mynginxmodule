#!/bin/sh
rm -rf /usr/local/nginx_echo
make clean
./configure --prefix=/usr/local/nginx_echo --add-module=/data/haoning/mygit/mynginxmodule/mynginx/echo --with-debug
make  CFLAGS="-g -O0"
make install
cp -f /data/haoning/mygit/mynginxmodule/mynginx/echo/nginx.conf /usr/local/nginx_echo/conf

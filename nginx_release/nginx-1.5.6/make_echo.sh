#!/bin/sh
rm -rf /usr/local/nginx_echo
make clean
./configure --prefix=/usr/local/nginx_echo --add-module=/root/haoning/mygit/mynginxmodule/mynginx/echo --with-debug
make 
make install
cp -f /root/haoning/mygit/mynginxmodule/mynginx/echo/nginx.conf /usr/local/nginx_echo/conf

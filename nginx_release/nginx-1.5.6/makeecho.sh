#!/bin/sh
rm -rf /usr/local/nginx_echo48
make clean
./configure --prefix=/usr/local/nginx_echo48 --add-module=/root/haoning/mygit/mynginxmodule/mynginx/echo-nginx-module-0.48
make 
make install
cp -f /root/haoning/mygit/mynginxmodule/mynginx/echo-nginx-module-0.48/nginx.conf /usr/local/nginx_echo48/conf

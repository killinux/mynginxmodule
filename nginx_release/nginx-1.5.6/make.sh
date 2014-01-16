#!/bin/sh
rm -rf /usr/local/nginx_hello
make clean
./configure --prefix=/usr/local/nginx_hello --add-module=/root/haoning/mygit/mynginxmodule/mynginx/helloworld --with-debug
make 
make install
cp -f /root/haoning/mygit/mynginxmodule/mynginx/helloworld/nginx.conf /usr/local/nginx_hello/conf

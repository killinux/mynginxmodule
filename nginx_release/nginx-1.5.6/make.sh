#!/bin/sh
rm -rf /usr/local/nginx_hello
./configure --prefix=/usr/local/nginx_hello --add-module=/root/mymodule/mynginxmodule/mynginx/helloworld
make 
make install
cp -f /root/mymodule/mynginxmodule/mynginx/helloworld/nginx.conf /usr/local/nginx_hello/conf

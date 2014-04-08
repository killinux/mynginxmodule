#!/bin/sh
rm -rf /usr/local/nginx_wordpress
make clean
./configure --prefix=/usr/local/nginx_wordpress --add-module=/data/haoning/mygit/mynginxmodule/mynginx/echo  --add-module=/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/mymodule/chapter5/upstream --with-debug
#make  CFLAGS="-g -O0"
make  CFLAGS="-ggdb3 -O0"
make install

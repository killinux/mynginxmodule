#!/bin/sh
rm -rf /usr/local/nginx_hello
make clean
./configure --prefix=/usr/local/nginx_hello  --add-module=/data/haoning/mygit/mynginxmodule/mynginx/helloworld  --with-debug
make  CFLAGS="-g -O0"
make install
cp -f /data/haoning/mygit/mynginxmodule/mynginx/helloworld/nginx.conf /usr/local/nginx_hello/conf

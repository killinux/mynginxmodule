#!/bin/sh
rm -rf /usr/local/nginx_two
make clean
./configure --prefix=/usr/local/nginx_two --add-module=/data/haoning/mygit/mynginxmodule/mynginx/echo --add-module=/data/haoning/mygit/mynginxmodule/mynginx/helloworld  --with-debug
make  CFLAGS="-g -O0"
make install
cp -f /data/haoning/mygit/mynginxmodule/mynginx/two/nginx.conf /usr/local/nginx_two/conf

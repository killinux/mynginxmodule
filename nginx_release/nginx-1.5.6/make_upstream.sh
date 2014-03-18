#!/bin/sh
rm -rf /usr/local/nginx_upstream
make clean
./configure --prefix=/usr/local/nginx_upstream --add-module=/data/haoning/mygit/mynginxmodule/mynginx/echo  --add-module=/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/mymodule/chapter5/upstream --with-debug
make  CFLAGS="-g -O0"
make install
#cp -f /data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/mymodule/chapter5/upstream/nginx.conf /usr/local/nginx_upstream/conf
cp -f  /data/haoning/mygit/mynginxmodule/html/nginx.conf /usr/local/nginx_upstream/conf/
rm -rf /usr/local/nginx_upstream/html
ln -s /data/haoning/mygit/mynginxmodule/html /usr/local/nginx_upstream/html

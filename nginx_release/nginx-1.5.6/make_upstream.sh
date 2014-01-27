#!/bin/sh
rm -rf /usr/local/nginx_upstream
make clean
./configure --prefix=/usr/local/nginx_upstream --add-module=/data/haoning/mygit/mynginxmodule/mynginx/source/chapter5/upstream --with-debug
make 
make install
cp -f /data/haoning/mygit/mynginxmodule/mynginx/source/chapter5/upstream/nginx.conf /usr/local/nginx_upstream/conf

#!/bin/sh
rm -rf /usr/local/nginx_helloworld
make clean
#./configure --prefix=/usr/local/nginx_helloworld  --add-module=/data/haoning/mygit/mynginxmodule/mynginx/hello_world  --add-module=/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/mymodule/chapter5/upstream --with-debug
./configure --prefix=/usr/local/nginx_helloworld  --add-module=/data/haoning/mygit/mynginxmodule/mynginx/hello_world --add-module=/data/haoning/mygit/mynginxmodule/mynginx/filter --with-debug
#./configure --prefix=/usr/local/nginx_helloworld --add-module=/data/haoning/mygit/mynginxmodule/mynginx/filter --with-debug
#make  CFLAGS="-g -O0"
make  CFLAGS="-ggdb3 -O0"
make install
#cp -f  /data/haoning/mygit/mynginxmodule/mynginx/hello_world/nginx.conf /usr/local/nginx_helloworld/conf
cp -f  /data/haoning/mygit/mynginxmodule/mynginx/filter/nginx.conf /usr/local/nginx_helloworld/conf

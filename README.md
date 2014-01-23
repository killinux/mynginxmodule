mynginxmodule
=============

nginx test
git clone https://github.com/killinux/mynginxmodule.git
cd mynginxmodule/
mkdir mynginx
cd mynginx/
git add .
git commit -m "hello world"
git push



.git/config 


[core]
        repositoryformatversion = 0
        filemode = true
        bare = false
        logallrefupdates = true
[remote "origin"]
        fetch = +refs/heads/*:refs/remotes/origin/*
        url = https://killinux@github.com/killinux/mynginxmodule.git
[branch "master"]
        remote = origin
        merge = refs/heads/master


ctags -R -f /data/haoning/mygit/mynginxmodule/nginxtags /data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6 /usr/include/ /data/haoning/mygit/mynginxmodule/mynginx/helloworld/ /data/haoning/mygit/mynginxmodule/mynginx/echo-nginx-module-0.48 /data/haoning/mygit/mynginxmodule/mynginx/echo /data/haoning/mygit/mynginxmodule/mynginx/source/chapter5/upstream 
test

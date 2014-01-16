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


ctags -R -f /root/haoning/mygit/mynginxmodule/nginxtags /root/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6 /usr/include/ /root/haoning/mygit/mynginxmodule/mynginx/helloworld/ /root/haoning/mygit/mynginxmodule/mynginx/echo-nginx-module-0.48 /root/haoning/mygit/mynginxmodule/mynginx/echo

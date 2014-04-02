
default:	build

clean:
	rm -rf Makefile objs

build:
	$(MAKE) -f objs/Makefile
	$(MAKE) -f objs/Makefile manpage

install:
	$(MAKE) -f objs/Makefile install

upgrade:
	/usr/local/nginx_helloworld/sbin/nginx -t

	kill -USR2 `cat /usr/local/nginx_helloworld/logs/nginx.pid`
	sleep 1
	test -f /usr/local/nginx_helloworld/logs/nginx.pid.oldbin

	kill -QUIT `cat /usr/local/nginx_helloworld/logs/nginx.pid.oldbin`

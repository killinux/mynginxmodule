#!/bin/sh  
/usr/bin/spawn-fcgi -a 127.0.0.1 -p 9000 -u haoning -g haoning -f /usr/bin/php-cgi -P /var/run/fastcgi-php.pid  

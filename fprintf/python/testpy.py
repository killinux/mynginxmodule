#!/usr/bin/python
import time
import redis
file_object = open('thefile.txt', 'w+')
file_object.write('haohao\n')
time.sleep(1)
file_object.write('ningning\n')
rediskey=""
r = redis.Redis(host='10.72.88.111', port=11093)
i = 1
start = time.clock()
while i<=10000:
    if(i%1000==0):
        time.sleep(0.1)
        print i
    rediskey= r.randomkey()
    file_object.write(rediskey+'\n')
    if(rediskey!=''):
        i+=1
print " cost %s second"%(time.clock()-start)
file_object.close( )

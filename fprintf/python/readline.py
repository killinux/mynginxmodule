#!/usr/bin/python
import time
#import redis
#rediskey=""
#r = redis.Redis(host='10.72.88.111', port=11093)
i = 1
start = time.clock()
f = open("bigFile.txt", "r")  
while True:  
    line = f.readline()  
    if line:  
       # pass    # do something here  
        print line 
    else:  
        break  
f.close()  
print " cost %s second"%(time.clock()-start)

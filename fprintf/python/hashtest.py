#!/usr/bin/python
import time
#thiskey="8ddbf33ad665010b2f62beb7"
start=time.clock()
def _key_hash( key) :
    hash = 5381
    length = len(key)
    for i in xrange(length) : 
        hash = ((hash << 5) + hash ) + ord(key[i])
    return hash
r11090 ="0"#        redis.Redis(host='10.75.22.239', port=11090)
r11091 ="1"#        redis.Redis(host='10.75.22.239', port=11091)
r11092 ="2"#        redis.Redis(host='10.75.22.239', port=11092)
r11093 ="3"#        redis.Redis(host='10.75.22.239', port=11093)
r11094 ="4"#        redis.Redis(host='10.75.22.240', port=11094)
r11095 ="5"#        redis.Redis(host='10.75.22.240', port=11095)
r11096 ="6"#        redis.Redis(host='10.75.22.240', port=11096)
r11097 ="7"#        redis.Redis(host='10.75.22.240', port=11097)
file_object = open('nonefile.txt', 'w+')
def printkey(thiskey):
    s=_key_hash(thiskey)%8
    if(s==0):
        client=r11090
    elif(s==1):
        client=r11091 
    elif(s==2):                                                                                                                        
        client=r11092
    elif(s==3):                                                                                                                                                    
        client=r11093
    elif(s==4):                                                                                                                                                    
        client=r11094
    elif(s==5):                                                                                                                                                    
        client=r11095
    elif(s==6):                                                                                                                                                    
        client=r11096
    elif(s==7):                                                                                                                                                    
        client=r11097
    else:                                                                                                                                                      
        print thiskey+" hasherror"
        return -1;
    thisvalue=client#.get(thiskey)
    if(thisvalue==None):
        print "error"
        file_object.write("error:"+thiskey+" "+thisvalue +"\n")
    else:
        file_object.write("right:"+thiskey+" "+thisvalue+"\n")
        #pass
#printkey(thiskey)
f = open("bigFile.txt", "r")  
i=0
while True:  
    i+=1;
    if(i%1000==0):
        time.sleep(0.1)
        print i 
    line = f.readline()  
    if line:  
        printkey(line.strip())
    else:  
        break  
f.close()  


file_object.close()
print " cost %s second"%(time.clock()-start)

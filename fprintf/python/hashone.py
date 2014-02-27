#!/usr/bin/python
import time
#thiskey="8ddbf33ad665010b2f62beb7"
thiskey="42d6bc1a3d6d28e4cde404d5"
def _key_hash( key) :
    hash = 5381
    length = len(key)
    for i in xrange(length) : 
        hash = ((hash << 5) + hash ) + ord(key[i])
    return hash
s=_key_hash(thiskey)%8
print s

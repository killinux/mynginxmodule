#!/usr/bin/python
def _key_hash( key) :
    hash = 5381
    length = len(key)
    for i in xrange(length) : 
        hash = ((hash << 5) + hash ) + ord(key[i])
    return hash
print _key_hash("8ddbf33ad665010b2f62beb7")

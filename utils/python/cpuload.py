#!/usr/bin/python
import time
import random

#def current_time_millis():
#    return int(round(time.time() * 1000))

def load():
    while True:
        print (random.random()*100)**(random.random()*10) / ((random.random()*100)**(random.random()*10))
def idle():
    while True:
        time.sleep(1)

if __name__=="__main__":
    #print "Start intence cpu overload fo shizzle"
    #load()
    idle()

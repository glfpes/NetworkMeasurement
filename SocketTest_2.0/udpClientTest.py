#!/usr/bin/env python
from SocketModule import *
from GlobleVariable import *
import time
import datetime

if __name__ == '__main__': 
       
    ud = UDPClient(SOCKET_UDP_IP,SOCKET_UDP_PORT)
    currentTime = GetTimeStamp() #get current time stamp
    if ud.SendMsg(currentTime):
        msg = ud.RecvMsg()  #receive offset time between client and server
        print 'feedback msg:',msg
    ud.Close()
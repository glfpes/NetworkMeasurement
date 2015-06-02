#!/usr/bin/env python

from SocketModule import *
from GlobleVariable import *


if __name__ == '__main__':
    us = UDPServer(SOCKET_UDP_IP,SOCKET_UDP_PORT)
    if us.StartBind():
        while True:
            recvMsg = us.RecvClientMsg()  #waiting for data from different client
            timeOffsetMsg = GetOffsetTime(recvMsg)  #get offset time(client to server) and send back to client
            print timeOffsetMsg
            us.SendFeedbackMsg(timeOffsetMsg)
        
    us.Close()
        
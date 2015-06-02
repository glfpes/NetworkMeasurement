import socket
import time
import threading
import sys
from GlobleVariable import *
from SocketModule import *

'''        
if __name__ == '__main__':
    print 'main Func'
    try:
        clientSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        serverIP = '127.0.0.1'
        serverPort = 9999
        print 'a'
        clientSocket.connect((serverIP,serverPort))
        print 'b'
        print clientSocket.recv(1024)
    #     for data in ['Michael', 'Tracy', 'Sarah']:
    #         clientSocket.send(data)
    #         print clientSocket.recv(1024)
        
        data = SetSocketMsg('127.0.0.1',PROTOCOL_UDP)
    
        GetSocketMsg('ip:,protocol:')
        print 'send',data
        clientSocket.send(data)
        
        tmp =  clientSocket.recv(1024)
        print 'get',tmp
        clientSocket.send('exit')
        clientSocket.close()
    except socket.error, arg:
        print sys.exc_info()
        print 'socket.error,',socket.error
        (errno,err_msg) = arg
        print 'Connection server failed:%s,errno=%d'%(err_msg,errno)
'''
 
if __name__ == '__main__':
    tp = TCPClient(SOCKET_TCP_IP,SOCKET_TCP_PORT)
    if tp.StartConnection():
        msg = {NETWORK_IP:'www.baidu.com',NETWORK_PROTOCOL:'ICMP'}
        tp.SendMsg(SetSocketMsg(msg))
        rsg = tp.RecvMsg()
        print 'Get Info from server:'
        rsgDic = GetSocketMsg(rsg)
        for key,value in rsgDic.items():
            print key,value
            
        tp.Close()
    print 'end'

    

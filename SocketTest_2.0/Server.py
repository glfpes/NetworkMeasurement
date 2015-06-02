import socket
import time
import threading 

from SocketModule import *
from GlobleVariable import *
import threading
from InterfaceFunc import *


#define our own thread to deal with 
def MyThread(clientSocket,clientAddr):
    print 'MyThread to deal with connection from %s:%s'%(clientAddr)
    msg =  clientSocket.recv(SOCKET_BUFFER_SIZE)
    
    detailMsg = GetSocketMsg(msg)  #formmat msg to dict we have defined in GlobleVariable
    print 'detailMsg:',detailMsg
    
    sendMsg = {} #msg which feedback to client include delay,bandwidth and so on
    
    if detailMsg[PROTOCOL_PROTOCOL] == 'TCP':
        print "TCP operation--iperf"
        sendMsg = GetTCPNetworkInfo(detailMsg[PROTOCOL_IP])
        
    elif detailMsg['protocol'] == 'UDP':
        print 'UDP operation--iperf'        
        sendMsg = GetUDPNetworkInfo(detailMsg[PROTOCOL_IP])#interface you need to override
        
    elif detailMsg['protocol'] == 'ICMP':
        print 'ICMP operation--ping'
        sendMsg = GetICMPNetworkInfo(detailMsg[PROTOCOL_IP])
        
    else:
        pass
            
    clientSocket.send(SetSocketMsg(sendMsg))  #send feedback msg to client
    clientSocket.close() #close socket
    print 'End MyThread to deal with connection'

if __name__ == '__main__':
    tpServer = TCPServer(SOCKET_TCP_IP,SOCKET_TCP_PORT)
    if tpServer.StartBind():
        #always working at background to deal with connection from client
        while True:
            clientSocket,clientAddr = tpServer.AcceptConnection()
            if clientAddr==None and clientAddr==None:
                continue #if we get none info
            #create new thread to deal with every connection from different Client            
            t = threading.Thread(target=MyThread,args=(clientSocket,clientAddr))
            t.start()
        tpServer.Close()  

    
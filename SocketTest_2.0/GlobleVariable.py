#!/usr/bin/env python

import time

PROTOCOL_UDP = 'UDP'
PROTOCOL_TCP = 'TCP'
PROTOCOL_ICMP = 'ICMP'
PROTOCOL_PROTOCOL = 'protocol'
PROTOCOL_IP = 'ip'

#DEFAULT IP AND PORT OF TCP
SOCKET_TCP_IP = '127.0.0.1'
SOCKET_TCP_PORT = 9999

#DEFAULT IP AND PORT OF UDP
SOCKET_UDP_IP = '127.0.0.1'
SOCKET_UDP_PORT = 11111

SOCKET_BUFFER_SIZE = 1024  #packet size of socket(send/receive) 
SOCKET_TIME_OUT = 8

SOCKET_MAX_CLIENT = 10     #max connection num from client

#define attribute
NETWORK_BANDWITH = 'bandwidth'   
NETWORK_DELAY = 'delay'          
NETWORK_JITTER = 'jitter'        
NETWORK_LOSS = 'loss'            
NETWORK_CONGESTION = 'congestion'
NETWORK_AVAIL = 'availability'   

NETWORK_IP = 'ip'
NETWORK_PROTOCOL = 'protocol'

FILE_PATH_UDP = 'udpfile.txt'

#func,deal with string
def SetSocketMsg(dicMsg):
    print 'SetSocketMsg,msg:',dicMsg
    msg = ''
    for k,v in dicMsg.items():
        print k,v
        if msg == '':
            msg += '%s:%s'%(k,v) #format dict to string which is 'key:value,key:value,key:value...'
        else:
            msg += ',%s:%s'%(k,v)
        
    print 'End SetSocketMsg,msg is:',msg
    return msg


#transform str to dic 
def GetSocketMsg(msg):
    print 'GetSocketMsg'
    socketMsg = {}
    tmpList = msg.split(',')
    for i in tmpList:
        tmp = i.split(':')
        socketMsg[tmp[0]] = tmp[1]
        if tmp[1] == "":
            print "[key:%s],value is ''"%tmp[0]
    print 'End GetSocketMsg,msg is:',socketMsg
    return socketMsg

#get time stamp which is type(float) ,we only keep 9 bin after .,return type(str)
def GetTimeStamp():
    return '%.9f'%time.time()

#get offset time:between timstampstr and currenttime
def GetOffsetTime(timeStampStr):
    currentTime = time.time()
    print '%.9f'%currentTime
    offsetTime = currentTime - float(timeStampStr)
    print '%.9f'%offsetTime
    if offsetTime > 1:
        return '%.3f (s)'%offsetTime
    else:
        return '%.3f (ms)'%(offsetTime*1000)
    


#to get network condition in udpfile.txt;return dict
def ReadIperfUDPFile(filePath = FILE_PATH_UDP):
    print 'StartReadIperfUDPFile'
    f = open(FILE_PATH_UDP)       #open file  
    lineStr = f.readline()
    lastLineStr = lineStr  # get string of last line in file
    while lineStr:
        lastLineStr = lineStr
        print 'lastLineStr',lastLineStr
        lineStr = f.readline()
    f.close()  #close open
    print lastLineStr
    
    #Init DEFAULT
    networkDict = {NETWORK_BANDWITH:'',NETWORK_JITTER:'',NETWORK_LOSS:'',NETWORK_CONGESTION:'NO',NETWORK_AVAIL:'YES'}
    #to get network info in lastLineStr
    if not -1 == lastLineStr.find('datagrams'):
        print 'fail connection'  #if str contains 'datagrams' which means failing connecting to server
        networkDict[NETWORK_AVAIL] = 'NO'  #not available to connect
        networkDict[NETWORK_CONGESTION] = ''
    else:
        tmpList = lastLineStr.split()  #split by ' '
        ##testtest
        for index,value in enumerate(tmpList):
            print '[index:%d][value:%s]'%(index,value)
        ###
        
        bandwidth = tmpList[7]+tmpList[8]  #get bandwidth
        jitter =  tmpList[9] + tmpList[10]  #get jitter
        loss = tmpList[13][1:-1]   #delete ( and ) to get loss
        networkDict[NETWORK_BANDWITH] = bandwidth
        networkDict[NETWORK_JITTER] = jitter
        networkDict[NETWORK_LOSS] = loss
    #print networkDict    
    print 'End StartReadIperfUDPFile'
    return networkDict

    
    
    
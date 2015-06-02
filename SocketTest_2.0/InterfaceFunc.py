#!/usr/bin/env python
from GlobleVariable import *
import os,sys,string,time
from SocketModule import *
#####UDP Thread######

def UDPThread_Iperf(ip,sendMsg):
    print 'UDPThread_Iperf:start iperf'
    os.system('iperf -u -c 192.168.1.152 -t 5 -i 1 > udpfile.txt')
    print 'end iperf'
    msg = ReadIperfUDPFile()
    for key,value in msg.items():
        sendMsg[key] = value #update info like: bandwidth,loss,jitter and so on
    print 'udp iperf,',sendMsg
    
    
def UDPThread_Delay(ip,sendMsg):
    print 'UDPThread_Iperf:start get delay info'
    #get delay info
    ud = UDPClient(SOCKET_UDP_IP,SOCKET_UDP_PORT)
    currentTime = GetTimeStamp() #get current time stamp
    msg = ''
    if ud.SendMsg(currentTime):
        msg = ud.RecvMsg()  #receive offset time between client and server
        print 'delay msg:',msg
    ud.Close()
    #end get delayinfo 
    sendMsg[NETWORK_DELAY] = msg #update delay info
    print 'udp delay,',sendMsg

#######################

#override TCP
#input:ip addr;output:dict of TCP network condition
def GetTCPNetworkInfo(ip):
    print ''
    return {}

#override TCP
#input:ip addr;output:dict of UDP network condition
def GetUDPNetworkInfo(ip):
    
    #sendMsg = {NETWORK_BANDWITH:'12Mps',NETWORK_DELAY:timeInfo,NETWORK_JITTER:'0.9ms',NETWORK_LOSS:'0.9%',NETWORK_CONGESTION:'yes',NETWORK_AVAIL:'yes'}
    '''
    print 'start iperf'
    os.system('iperf -u -c 192.168.1.152 -t 5 -i 1 > udpfile.txt')
    print 'end iperf'
    sendMsg = ReadIperfUDPFile()
    
    print 'start get delay info'
    #get delay info
    ud = UDPClient(SOCKET_UDP_IP,SOCKET_UDP_PORT)
    currentTime = GetTimeStamp() #get current time stamp
    if ud.SendMsg(currentTime):
        msg = ud.RecvMsg()  #receive offset time between client and server
        print 'feedback msg:',msg
        sendMsg[NETWORK_DELAY] = msg
    ud.Close()
    #end get delayinfo 
    print 'GetNetworkUDP',sendMsg
    return sendMsg
    '''
    sendMsg = {}
    t1 = threading.Thread(target=UDPThread_Iperf,args=(ip,sendMsg))
    t2 = threading.Thread(target=UDPThread_Delay,args=(ip,sendMsg))
    t1.start()
    t2.start()
    t1.join()
    t2.join()  #block until thread t1 and t2 end
    
    return sendMsg
    

#override TCP
#input:ip addr;output:dict of ICMP network condition
def GetICMPNetworkInfo(ip):
    ISOTIMEFORMAT='%Y-%m-%d_%X'
    time_char = time.strftime(ISOTIMEFORMAT, time.gmtime(time.time()))
    IP = ip
    num_to_send_string = "10"
    c_rate_raw = "0.3";
    s_bandwidth_raw = "10"
    command = "./ICMP/ICMP_Positive " + IP + " " + num_to_send_string + " " + c_rate_raw + " " + s_bandwidth_raw + " " + time_char
    os.system(command)

    connection_file = "./" + time_char + "_result.txt"
    f=open(connection_file)
    array=[]
    for line in f:
        array.append(string.atof(line))
        
    bandwidth_to_send = str(array[4]) + 'Mps'
    if IP == '127.0.0.1':
        bandwidth_to_send = 'localhost'
    delay_to_send = str(array[0])
    jitter_to_send = str(array[1])
    loss_to_send = str(array[2])
    if(array[5] == 1):
        congestion_to_send = 'yes'
    elif(array[5] == 0):
        congestion_to_send = 'no'
    if(array[3] == 1):
        available_to_send = 'yes'
    elif(array[3] == 0):
        available_to_send = 'no'
    
    
    sendMsg = {NETWORK_BANDWITH:bandwidth_to_send,NETWORK_DELAY:delay_to_send,NETWORK_JITTER:jitter_to_send,NETWORK_LOSS:loss_to_send,NETWORK_CONGESTION:congestion_to_send,NETWORK_AVAIL:available_to_send}
   
    delete_connection_file = "rm "+ connection_file
    os.system(delete_connection_file)
    return sendMsg

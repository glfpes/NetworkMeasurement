/***************************
对外接口:
构造函数 PacketLoss_ICMP_Positive(int OS, int packets_to_send, string IP) 可以不填参数，也可以填三个参数，三个参数依次是OS类型(0:windows 1:linux)，要发几个icmp测试数据报，以及目标的域名或IP地址
在设置好3个参数后，可以执行下列操作
int get_received()  返回收到了多少个包，为-1说明文件存储读取失败，为0 ~ i 说明返回了对应的包数。关键函数。
float get_loss_rate() 返回丢包率
bool isAvailable 返回可用性，1为可用 0为不可用
***************************/



#ifndef PACKETLOSS_ICMP_POSITIVE_H
#define PACKETLOSS_ICMP_POSITIVE_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

class PacketLoss_ICMP_Positive
{
    public:
        PacketLoss_ICMP_Positive();
        PacketLoss_ICMP_Positive(int OS, int packets_to_send, string IP);


		int get_received();		//get the number received after test
        float get_loss_rate();			//get the packet loss rate
        bool isAvailable();				//decide if the connection is available

        virtual ~PacketLoss_ICMP_Positive();
    protected:

    private:
		void setOS(int i);		////0 windows 1 linux
        void setIP(string  IP);	//set the destination IP or URL
        void set_packets_to_send(int num);	//decide how many packets you want to test
        //int getOS();
        //string getIP();
        //int get_packets_to_send();

    	int OS; //0 windows 1 linux
        string IP_to_test;
        int packets_to_send;

        int received;
        float receive_rate;
        float loss_rate;
};

#endif // PACKETLOSS_ICMP_POSITIVE_H

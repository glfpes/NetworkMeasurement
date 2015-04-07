/***************************
对外接口:
构造函数 PacketLoss_ICMP_Positive(int OS, int packets_to_send, string IP) 填三个参数，三个参数依次是OS类型(0:windows 1:linux)，要发几个icmp测试数据报，以及目标的域名或IP地址，设置完参数后进行测试并存储数据到1.txt中
最后分析所得的数据，将各次延迟填入delay链表中，将最终收到包个数填到received数据中。关键函数。
它调用下面2个函数
int get_received()  分析1.txt，统计返回收到了多少个包，为-1说明文件存储读取失败，为0 ~ i 说明返回了对应的包数。
int get_latency(int OS) 将所有包的延迟时间记录到私有链表delay中，返回0操作完成，返回-1读取文件有问题，若某包超时，超时时间为4000ms计入延迟之中, OS设为0为win，设为1为linux

在设置好3个参数后，可以执行下列操作（外部函数调用接口）
float get_loss_rate() 返回丢包率
bool isAvailable 返回可用性，1为可用 0为不可用
float get_average_latency();	//get average latency
float get_jitter();				//get jitter抖动值
***************************/



#ifndef PACKETLOSS_ICMP_POSITIVE_H
#define PACKETLOSS_ICMP_POSITIVE_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <stdio.h>
#include <math.h>
using namespace std;

class PacketLoss_ICMP_Positive
{
    public:
        PacketLoss_ICMP_Positive();
        PacketLoss_ICMP_Positive(int packets_to_send, string IP, float c_rate, float s_bandwidth);



		float get_loss_rate();			//get the packet loss rate
        bool isAvailable();				//decide if the connection is available
		float get_average_latency();	//get average latency
		float get_jitter();				//get jitter抖动值	,求出标准差

		float get_bandwidth();
		bool isCongestion();



        virtual ~PacketLoss_ICMP_Positive();
    private:
		//Private Methods
        int ping_analyse();
        int bing_analyse();

		//Private Parameters
        string IP_to_test;
        int packets_to_send;
        float congestion_rate; //if (available bandwidth/set bandwidth) > congestion_rate, it is viewed as non-congested return 0
        float set_bandwidth;  //Mbps

        int received;
		list<float> delay;

        float bandwidth;
		bool congestion; //0:non congested, 1:congested
        float receive_rate;
        float loss_rate;
		float delay_average;
		float jitter;

};

#endif // PACKETLOSS_ICMP_POSITIVE_H

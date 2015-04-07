/***************************
����ӿ�:
���캯�� PacketLoss_ICMP_Positive(int OS, int packets_to_send, string IP) ��������������������������OS����(0:windows 1:linux)��Ҫ������icmp�������ݱ����Լ�Ŀ���������IP��ַ���������������в��Բ��洢���ݵ�1.txt��
���������õ����ݣ��������ӳ�����delay�����У��������յ��������received�����С��ؼ�������
����������2������
int get_received()  ����1.txt��ͳ�Ʒ����յ��˶��ٸ�����Ϊ-1˵���ļ��洢��ȡʧ�ܣ�Ϊ0 ~ i ˵�������˶�Ӧ�İ�����
int get_latency(int OS) �����а����ӳ�ʱ���¼��˽������delay�У�����0������ɣ�����-1��ȡ�ļ������⣬��ĳ����ʱ����ʱʱ��Ϊ4000ms�����ӳ�֮��, OS��Ϊ0Ϊwin����Ϊ1Ϊlinux

�����ú�3�������󣬿���ִ�����в������ⲿ�������ýӿڣ�
float get_loss_rate() ���ض�����
bool isAvailable ���ؿ����ԣ�1Ϊ���� 0Ϊ������
float get_average_latency();	//get average latency
float get_jitter();				//get jitter����ֵ
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
		float get_jitter();				//get jitter����ֵ	,�����׼��

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

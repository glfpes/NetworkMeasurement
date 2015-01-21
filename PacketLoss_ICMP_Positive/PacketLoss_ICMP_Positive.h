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
        PacketLoss_ICMP_Positive(int OS, int packets_to_send, string IP);


		
		float get_loss_rate();			//get the packet loss rate
        bool isAvailable();				//decide if the connection is available
		float get_average_latency();	//get average latency
		float get_jitter();				//get jitter����ֵ	,�����׼��		

        virtual ~PacketLoss_ICMP_Positive();

    protected:

    private:
		//Private Methods
		void setOS(int i);		////0 windows 1 linux
        void setIP(string  IP);	//set the destination IP or URL
        void set_packets_to_send(int num);	//decide how many packets you want to test
        //int getOS();
        //string getIP();
        //int get_packets_to_send();

		int get_received();		//get the number received after test
		int get_latency(int OS);		//set list delay which contains delay result for each test packet. return 0 for success and return -1 for wrong file read.
        

		//Private Parameters
    	int OS; //0 windows 1 linux
        string IP_to_test;
        int packets_to_send;

        int received;
		list<int> delay;

        float receive_rate;
        float loss_rate;
		float delay_average;
		float tremble;
};

#endif // PACKETLOSS_ICMP_POSITIVE_H

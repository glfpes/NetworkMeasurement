/***************************
����ӿ�:
���캯�� PacketLoss_ICMP_Positive(int OS, int packets_to_send, string IP) ���Բ��������Ҳ������������������������������OS����(0:windows 1:linux)��Ҫ������icmp�������ݱ����Լ�Ŀ���������IP��ַ
�����ú�3�������󣬿���ִ�����в���
int get_received()  �����յ��˶��ٸ�����Ϊ-1˵���ļ��洢��ȡʧ�ܣ�Ϊ0 ~ i ˵�������˶�Ӧ�İ������ؼ�������
float get_loss_rate() ���ض�����
bool isAvailable ���ؿ����ԣ�1Ϊ���� 0Ϊ������
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

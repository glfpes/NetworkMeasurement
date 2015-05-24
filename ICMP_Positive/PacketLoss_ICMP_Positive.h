#ifndef PACKETLOSS_ICMP_POSITIVE_H
#define PACKETLOSS_ICMP_POSITIVE_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <math.h>

using namespace std;

class PacketLoss_ICMP_Positive
{
    public:
        PacketLoss_ICMP_Positive();
        PacketLoss_ICMP_Positive(float packets_to_send, string IP, float c_rate, float s_bandwidth,string timestamp);



		float get_loss_rate();
        bool isAvailable();
		float get_average_latency();
		float get_jitter();

		float get_bandwidth();
		bool isCongestion();

        void ping_analyse();
        void bing_analyse();

        void delete_tmp();

        virtual ~PacketLoss_ICMP_Positive();
    private:
        string IP_to_test;
        float packets_to_send;
        float congestion_rate; //if (available bandwidth/set bandwidth) > congestion_rate, it is viewed as non-congested return 0
        float set_bandwidth;  //Mbps

        float received;
		list<float> delay;

        float bandwidth;
		bool congestion; //0:non congested, 1:congested
        float receive_rate;
        float loss_rate;
		float delay_average;
		float jitter;

        string time_now;
        string tmp_file_ping;
        string tmp_file_bing;
};

#endif // PACKETLOSS_ICMP_POSITIVE_H

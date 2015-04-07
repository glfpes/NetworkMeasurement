#include "PacketLoss_ICMP_Positive.h"

int main(int argc, char* argv[])
{
	//int num_of_para = argc;

	//char* IP = argv[1];
	//char* num_to_send_string = argv[2];

    char* IP = "www.sina.com.cn";
    char* num_to_send_string = "10";


	int num = atoi(num_to_send_string);


	PacketLoss_ICMP_Positive PacketLoss_ICMP(num, IP);
	float average_delay = PacketLoss_ICMP.get_average_latency();
	float jitter = PacketLoss_ICMP.get_jitter();
	float loss_rate = PacketLoss_ICMP.get_loss_rate();
	bool av = PacketLoss_ICMP.isAvailable();

	ofstream out;
	out.open("result.txt");
	out<<average_delay<<endl
		<<jitter<<endl
		<<loss_rate<<endl
		<<av<<endl;;

	cout<<"Average latency is "<<average_delay<<endl;
	cout<<"Jitter(Standard deviation) is "<<jitter<<endl;
	cout<<"Packet Loss Rate is "<<loss_rate<<endl;
	cout<<"Availablity is "<<av<<endl;

	return 0;
}

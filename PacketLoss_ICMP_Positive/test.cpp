#include "PacketLoss_ICMP_Positive.h"

int main(int argc, char* argv[])
{
	int num_of_para = argc;
	char* OS_string = argv[1];
	char* IP = argv[2];
	char* num_to_send_string = argv[3];
	
	int OS = atoi(OS_string);
	int num = atoi(num_to_send_string);
	cout<<OS<<endl<<IP<<endl<<num<<endl;

	PacketLoss_ICMP_Positive PacketLoss_ICMP(OS, num, IP);
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

	/*
	cout<<"Please select your OS, 0 for windows and 1 for linux: "<<endl;
	int OS = 0;
	cin>>OS;
	cout<<"Please input the Destination you want to test: "<<endl;
    string IP("");
    cin>>IP;
	cout<<"Please input the number of ICMP packets you want to test: "<<endl;
	int num = 4;
	cin>>num;


	PacketLoss_ICMP_Positive PacketLoss_ICMP(OS, num, IP);
	*/

/*
	int OS = 0;
	int num = 3;
	string IP = "www.baidu.com";
	PacketLoss_ICMP_Positive PacketLoss_ICMP(OS, num, IP);
*/	
	/*
	float average_delay = PacketLoss_ICMP.get_average_latency();
	cout<<"Average latency is "<<average_delay<<endl;
	float jitter = PacketLoss_ICMP.get_jitter();
	cout<<"Jitter(Standard deviation) is "<<jitter<<endl;

	float loss_rate = PacketLoss_ICMP.get_loss_rate();
	bool av = PacketLoss_ICMP.isAvailable();
	cout<<"Packet Loss Rate is "<<loss_rate<<endl;
	cout<<"Availablity is "<<av<<endl;
	*/
	

	return 0;
}

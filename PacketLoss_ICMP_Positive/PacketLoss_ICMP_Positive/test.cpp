#include "PacketLoss_ICMP_Positive.h"

int main()
{


	cout<<"Please input the Destination you want to test: "<<endl;
    string IP("");
    cin>>IP;
	cout<<"Please input the number of ICMP packets you want to test: "<<endl;
	int num = 4;
	cin>>num;
	cout<<"Please select your OS, 0 for windows and 1 for linux: "<<endl;
	int OS = 0;
	cin>>OS;

	PacketLoss_ICMP_Positive PacketLoss_ICMP(OS, num, IP);


/*
	int OS = 1;
	int num = 4;
	string IP = "127.0.0.1";
	PacketLoss_ICMP_Positive PacketLoss_ICMP(OS, num, IP);
*/

	PacketLoss_ICMP.get_received();

	float loss_rate = PacketLoss_ICMP.get_loss_rate();
	bool av = PacketLoss_ICMP.isAvailable();
	cout<<"Packet Loss Rate is "<<loss_rate<<endl;
	cout<<"Availablity is "<<av<<endl;



	return 0;
}

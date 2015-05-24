#include "PacketLoss_ICMP_Positive.h"


int main(int argc, char* argv[])
{

	int num_of_para = argc;

	char* IP = argv[1];
	char* num_to_send_string = argv[2];
	char* c_rate_raw = argv[3];
	char* s_bandwidth_raw = argv[4];
	char* timestamp = argv[5];

/*
    char* IP = "www.sina.com.cn";
    char* num_to_send_string = "10";
    char* c_rate_raw = "0.30";
   	char* s_bandwidth_raw = "10";
   	char* timestamp = "123.12";
*/

	float num = atof(num_to_send_string);

	float c_rate = atof(c_rate_raw);
	float s_bandwidth = atof(s_bandwidth_raw);
	string timestamp_string(timestamp);
    cout<<"main function time stamp string"<<timestamp_string<<endl;

	PacketLoss_ICMP_Positive PacketLoss_ICMP(num, IP,c_rate,s_bandwidth,timestamp_string);



	float average_delay = PacketLoss_ICMP.get_average_latency();
	float jitter = PacketLoss_ICMP.get_jitter();
	float loss_rate = PacketLoss_ICMP.get_loss_rate();
	bool av = PacketLoss_ICMP.isAvailable();
	float bandwidth = PacketLoss_ICMP.get_bandwidth();
	bool isCongestion = PacketLoss_ICMP.isCongestion();
    PacketLoss_ICMP.delete_tmp();

	ofstream out;
	string tmp_result = "_result.txt";
	string conncection_file = timestamp_string + tmp_result;
	out.open(conncection_file.c_str());
	out<<average_delay<<endl
		<<jitter<<endl
		<<loss_rate<<endl
		<<av<<endl
		<<bandwidth<<endl
		<<isCongestion<<endl;

	cout<<"Average latency is "<<average_delay<<endl;
	cout<<"Jitter(Standard deviation) is "<<jitter<<endl;
	cout<<"Packet Loss Rate is "<<loss_rate<<endl;
	cout<<"Availablity is "<<av<<endl;

	cout<<"Available Bandwidth is "<<bandwidth<<"Mbps"<<endl;
	cout<<"Congestion Status: "<<isCongestion<<endl;







	return 0;
}

#include "PacketLoss_ICMP_Positive.h"

PacketLoss_ICMP_Positive::PacketLoss_ICMP_Positive()
{
	OS = 0;
	IP_to_test = "";
	packets_to_send = 0;
	received = 0;
	receive_rate = 0;
	loss_rate = 0;
	
}

PacketLoss_ICMP_Positive::PacketLoss_ICMP_Positive(int OS, int packets_to_send, string IP)
{
	this->OS = OS;
	this->packets_to_send = packets_to_send;
	this->IP_to_test = IP;
	received = 0;
	receive_rate = 0;
	loss_rate = 0;

	string ping_para = "";
	
	if (OS == 0)
	{
		
		ping_para = " -n ";
	}
	else if(OS == 1)
	{
		
		ping_para = " -c ";
	}

	char ctime[10] = "";
	sprintf(ctime,"%d",this->packets_to_send);
	string IP_to_send = "ping "+ this->IP_to_test+ ping_para + ctime + " >1.txt";

	cout<<IP_to_send<<endl;
	system(IP_to_send.c_str());

	this->get_received();
	this->get_latency(this->OS);
}

void PacketLoss_ICMP_Positive::setOS(int i)
{
	OS = i;
}

void PacketLoss_ICMP_Positive::setIP(std::string  IP)
{
	IP_to_test = IP;
}

void PacketLoss_ICMP_Positive::set_packets_to_send(int num)
{
	packets_to_send = num;
}

/*
int PacketLoss_ICMP_Positive::getOS()
{
	return OS;
}

string PacketLoss_ICMP_Positive::getIP()
{
	return IP_to_test;
}

int PacketLoss_ICMP_Positive::get_packets_to_send()
{
	return packets_to_send;
}
*/


int PacketLoss_ICMP_Positive::get_received()
{


	int received = 0;
	ifstream in("1.txt");
	if(in)
	{

		int line_to_scale = 0;
		if (OS == 0)
		{
			line_to_scale = 5;

		}
		else if(OS == 1)
		{
			line_to_scale = 4;
		
		}
		int count = 0;
		string lines;
		while (getline (in, lines))  // have no '\n',
		{
			cout << lines << endl;
			count++;
			if (count == this->packets_to_send + line_to_scale)	//反映结果的一行
			{
				string result = lines;
                if(OS == 1)
                {
                    result = "header " + result;
                }

				//需要处理数据，得到具体的丢失数量
                cout<<endl<<result<<endl;

				bool lock1 = 0;
				bool lock2 = 0;
				for(int i=0;result[i]!='\0';i++)
				{
					if(i>0)
					{
						if((result[i]>='0'&&result[i]<='9') && (result[i-1]<='0' || result[i-1]>='9') && lock2 == 0)
							lock1 = 1;
						else if((result[i-1]>='0'&& result[i-1]<='9') &&  (result[i]<='0' || result[i]>='9') && lock2 == 0)
							lock2 = 1;
						else if(result[i]>='0'&&result[i]<='9' && lock1==1 && lock2 == 1)
							received=(received*10)+result[i]-'0';
						else if((result[i-1]>='0'&& result[i-1]<='9') &&  (result[i]<='0' || result[i]>='9') && lock1==1 && lock2 == 1 )
							break;
					}
				}
			}
		}
		this->received = received;
		return this->received;
	}
	else
	{
		cerr << "some errors happened when reads the file.";
		return -1;
	}

}

int PacketLoss_ICMP_Positive::get_latency(int OS)
{
	ifstream in("1.txt");
	if(in)
	{
		if(OS == 0)
		{
			int count = 0;
			string lines;
		
			cout<<endl<<endl<<endl<<endl<<123<<endl;
			while (getline (in, lines))  // have no '\n',
			{
				count++;
				if(count > 2 && count < 3 + this->packets_to_send)
				{
					string result = lines;
					const string timeout = "超时";	// timeout time is 4000ms
					int if_time_out = result.find(timeout,0); //can't find will return -1	,
					if(if_time_out != -1)
					{
						delay.push_back(4000);
						cout<<"timeout"<<endl;
					}
					else
					{
						const string find_latency_pos = "时间=";
						int latency_pos = result.find(find_latency_pos,0) + 5;
					
						int latency_temp = 0;
					
						for(int i=latency_pos; result[i]!='m'; i++)
							latency_temp=(latency_temp*10)+result[i]-'0';
						delay.push_back(latency_temp);
					}
				}
			}
		}
		else if (OS == 1)
		{
				string lines;
                while (getline (in, lines))  // have no '\n',
                {
                         string result = lines;
                         const string find_latency_pos = "time=";
                         int find_anchor = result.find(find_latency_pos,0);
                         if(find_anchor != -1)
                         {
                                 int latency_pos = find_anchor + 5;
                                 int latency_temp = 0;

                                 for(int i=latency_pos; result[i]!=' '; i++)
                                 {
                                        latency_temp=(latency_temp*10)+result[i]-'0';

                                 }
                                delay.push_back(latency_temp);
                                cout<<latency_temp<<"------------"<<endl;
                         }
                }

                int lost_packet = this->packets_to_send - this->received;
                for(int i = 0; i < lost_packet; i++)
                {
                        delay.push_back(4000);
                        cout<<4000<<"------------"<<endl;
                }

		}

		//delay stores all latency numbers
		return 0;
	}
	else
	{
		cerr << "some errors happened when reads the file.";
		return -1;
	}

}

float PacketLoss_ICMP_Positive::get_average_latency()
{
	int total = 0;
	list<int>::iterator it;
	for(it = this->delay.begin(); it!= this->delay.end();it++)
	{
		total += *it;
	}
	this->delay_average = total/this->packets_to_send;
	return this->delay_average;
}

float PacketLoss_ICMP_Positive::get_jitter()
{
	return 0;
}

float PacketLoss_ICMP_Positive::get_loss_rate()
{
	float receive_rate = this->received/this->packets_to_send;
	float loss_rate = 1 - receive_rate;
	this->receive_rate = receive_rate;
	this->loss_rate = loss_rate;
	cout<<"--------------------------"<<endl;
	cout<<"Sent packet number is "<<this->packets_to_send<<endl;
	cout<<"Received packet number is "<<this->received<<endl;
	return loss_rate;

}

bool PacketLoss_ICMP_Positive::isAvailable()
{
	float receive_rate = this->received/this->packets_to_send;
	this->receive_rate = receive_rate;
	if(receive_rate !=0 )
			return true;
	else if(receive_rate == 0)
			return false;
}

PacketLoss_ICMP_Positive::~PacketLoss_ICMP_Positive()
{
    //dtor
}

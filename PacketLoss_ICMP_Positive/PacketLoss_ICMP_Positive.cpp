#include "PacketLoss_ICMP_Positive.h"

PacketLoss_ICMP_Positive::PacketLoss_ICMP_Positive()
{
	IP_to_test = "";
	packets_to_send = 0;
	received = 0;
	receive_rate = 0;
	loss_rate = 0;
}

PacketLoss_ICMP_Positive::PacketLoss_ICMP_Positive(int packets_to_send, string IP)
{

	this->packets_to_send = packets_to_send;
	this->IP_to_test = IP;
	received = 0;
	receive_rate = 0;
	loss_rate = 0;

	string ping_para = "";

	char ctime[10] = "";
	sprintf(ctime,"%d",this->packets_to_send);
	string IP_to_send = "ping "+ this->IP_to_test+ " -c " + ctime + " >1.txt" ;

	cout<<IP_to_send<<endl;
	system(IP_to_send.c_str());

	this->analyse();
}

//return 0 success, return -1 error
int PacketLoss_ICMP_Positive::analyse()
{
    int received_packets = 0;
	ifstream in("1.txt");
	if(in)
	{
        string lines;
        while (getline (in, lines))  // have no '\n',
        {
            string result = lines;
            const string find_latency_pos = "time=";
            int find_anchor = result.find(find_latency_pos,0);
            if(find_anchor != -1)
            {
                received_packets++;     //one more packet received

                //string analyse to find the digitial packet transmit time
                int latency_pos = find_anchor + 5;
                float latency_temp = 0;

                bool dotLocker = 0; //0:digits before dot; 1:digits after dot

                int k = 0; // total number of digits with dot

                int before_point = 0;   //total number of digits before dot with dot
                for(int i=latency_pos; result[i]!=' '; i++)
                {

                    if(result[i] =='.')
                    {
                        dotLocker = 1;
                        before_point++;
                    }

                    else if(dotLocker == 0)
                    {
                        latency_temp=(latency_temp*10)+result[i]-'0';
                        before_point++;
                    }
                    else if(dotLocker == 1)
                    {
                        latency_temp += (result[i]-'0')*pow(10,-1*(k-before_point+1));
                    }

                    k++;
                }
                delay.push_back(latency_temp);
                cout<<latency_temp<<"------------"<<endl;
            }
        }
        this->received = received_packets;  //received packets number

        int lost_packet = this->packets_to_send - this->received;
        for(int i = 0; i < lost_packet; i++)
        {
                delay.push_back(4000);
                cout<<4000<<"------------"<<endl;
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
	float total = 0;
	list<float>::iterator it;
	for(it = this->delay.begin(); it!= this->delay.end();it++)
	{
		total += *it;
	}
	this->delay_average = total/this->packets_to_send;
	return this->delay_average;
}

float PacketLoss_ICMP_Positive::get_jitter()
{
	float average = this->get_average_latency();
	float tempsum = 0;
	list<float>::iterator it;
	for(it = this->delay.begin(); it!= this->delay.end();it++)
	{
		tempsum += powf((*it-average),2);
	}
	float deviation = sqrtf(tempsum/this->packets_to_send);
	return deviation;
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

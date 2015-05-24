#include "PacketLoss_ICMP_Positive.h"

PacketLoss_ICMP_Positive::PacketLoss_ICMP_Positive()
{
	IP_to_test = "";
	packets_to_send = 0;
	received = 0;
	receive_rate = 0;
	loss_rate = 0;

	set_bandwidth = 10;

}

PacketLoss_ICMP_Positive::PacketLoss_ICMP_Positive(float packets_to_send, string IP, float c_rate, float s_bandwidth,string timestamp)
{

	this->packets_to_send = packets_to_send;
	this->IP_to_test = IP;
	this->congestion_rate = c_rate;
	this->set_bandwidth = s_bandwidth;

	this->received = 0;
    this->bandwidth = 0;
    this->congestion = 0;
	this->receive_rate = 0;
	this->loss_rate = 0;
	this->delay_average = 0;
	this->jitter = 0;


    this->time_now = timestamp;
    this->tmp_file_bing = this->time_now + "_bing.txt";
    this->tmp_file_ping = this->time_now + "_ping.txt";

    cout<<this->tmp_file_bing<<endl<<this->tmp_file_ping<<endl;

	string ping_para = "";

	char ctime[10] = "";
	sprintf(ctime,"%f",this->packets_to_send);
	cout<<ctime<<" float"<<endl;
	string IP_to_send = "ping "+ this->IP_to_test+ " -c " + ctime + " >" + this->tmp_file_ping;

	cout<<IP_to_send<<endl;
	system(IP_to_send.c_str());

	this->ping_analyse();
	if(this->isAvailable())
	{
        this->bing_analyse();
	}
	else
	{
        this->bandwidth = 0;
	}
}

//return 0 success, return -1 error
void PacketLoss_ICMP_Positive::ping_analyse()
{
    float received_packets = 0;
	ifstream in(this->tmp_file_ping);
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

        float lost_packet = this->packets_to_send - this->received;
        for(int i = 0; i < lost_packet; i++)
        {
                delay.push_back(4000);
                cout<<4000<<"------------"<<endl;
        }
		//delay stores all latency numbers
		//return 0;
	}
	else
	{
		cerr << "some errors happened when reads the file.";
		//return -1;
	}
}


void PacketLoss_ICMP_Positive::bing_analyse()
{
    string command = "bing -e 100 -z localhost " + this->IP_to_test + " >" + this->tmp_file_bing;
    cout<<command<<endl;
    system(command.c_str());
    ifstream in(this->tmp_file_bing);
    if(in)
    {
        string lines;
        string result;
        while (getline (in, lines))  // have no '\n',
        {
            result = lines;
        }
        cout<<result<<endl;
        const string find_latency_pos = "Mbps";
        int find_anchor = result.find(find_latency_pos,0);
        int latency_pos = find_anchor - 5;

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
        cout<<latency_temp<<endl;
        this->bandwidth = latency_temp;

        //return 0;
    }
    else
    {
        cerr << "some errors happened when reads the file.";
		//return -1;
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
	this->jitter = deviation;
	return this->jitter;
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

float PacketLoss_ICMP_Positive::get_bandwidth()
{
    return this->bandwidth;
}

bool PacketLoss_ICMP_Positive::isCongestion()
{
    float congestion_ratio = this->bandwidth/this->set_bandwidth;
    if(congestion_ratio > congestion_rate)
        return false;
    else
        return true;
}
void PacketLoss_ICMP_Positive::delete_tmp()
{
    string remove_str = "rm ";
    string delete_bing = remove_str + this->tmp_file_bing;
    string delete_ping = remove_str + this->tmp_file_ping;
    system(delete_bing.c_str());
    system(delete_ping.c_str());
    cout<<"Success delete"<<endl;
}

PacketLoss_ICMP_Positive::~PacketLoss_ICMP_Positive()
{
    //dtor

}

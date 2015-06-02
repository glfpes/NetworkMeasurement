#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>

using namespace std;

int main(int argc, char* argv[])
{

    string IP(argv[1]);
    string protocol(argv[2]);
    string temp_filename(argv[3]);

    string timestamp = temp_filename;
    temp_filename += "_temp_route.dat";

    string command = "traceroute " + protocol;
    command += " ";
    command += IP;
    command += ">";
    command += temp_filename;
    cout<<"command to linux: "<<command<<endl;
    system(command.c_str());

    ifstream in(temp_filename.c_str());
    if(in)
    {
        string lines;
        bool isFirstLine = true;
        list<string> route;
        list<string>::iterator it;
        while (getline (in, lines))  // have no '\n',
        {
            //ignore the first line's output
            if(isFirstLine)
            {
                isFirstLine = false;
                continue;
            }

            //fetch traceroute nodes, store them in the list data structure
            string result = lines;
            const string find_left = "(";
            const string find_right = ")";
            int find_left_loc = result.find(find_left,0);
            int find_right_loc = result.find(find_right,0);
            find_left_loc++;
            find_right_loc--;
            string temp = "";
            for(int i = find_left_loc; i <= find_right_loc; i++)
            {
                temp += result[i];
            }
            if(temp == "")
            {
                temp = "***";
            }
            route.push_back(temp);
            temp = "";

        }

        //output result into file timestamp_result.dat
        ofstream out;
        string conncection_file_traceroute = timestamp + "_result.dat";
        out.open(conncection_file_traceroute.c_str());
        for(it=route.begin();it!=route.end();it++)
        {
            out<<*it<<endl;
        }

        //erase temp file
        string remove_str = "rm ";
        remove_str += temp_filename;
        system(remove_str.c_str());
        cout<<"Success delete"<<endl;
    }
    else
    {
        cerr << "some errors happened when reads the file.";
    }

    return 0;
}

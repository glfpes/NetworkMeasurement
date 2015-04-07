import os,sys,string
IP = sys.argv[1]
num_to_send_string = sys.argv[2]
c_rate_raw = sys.argv[3]
s_bandwidth_raw = sys.argv[4]

command = "./ICMP_Positive " + IP + " " + num_to_send_string + " " + c_rate_raw + " " + s_bandwidth_raw

os.system(command)

f=open("result.txt")
array=[]
for line in f:
	array.append(string.atof(line))
for var in array:
	print var

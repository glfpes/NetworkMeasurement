Env:
----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
1, Install bing using "sudo apt-get install bing".
2, Assign authority to bing to permit it using socket by "sudo chmod u+s /usr/sbin/bing".
3, Makesure python is installed.



Run:
----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
Type in the following command to run the alpha edition program of Positive ICMP network measurement:

sudo python ./wrapper.py para1 para2 para3 para4

para1 ------------ The destination HOST we want to test.
para2 ------------ The number of ICMP packets we want to send.(10 is enough)
para3 ------------ The value of congestion we set.(Practical Bandwidth/Set Bandwidth < para3 is considered as congestion)
para4 ------------ The Set Bandwidth.(Physically link decides this)

We get some shell output and within the wrapper.py we got all six parameters listed in the array.
array[0]: Average Latency
array[1]: Jitter
array[2]: Packet loss rate
array[3]: Availabiliy
array[4]: Practical Bandwidth
array[5]: Congestion Status

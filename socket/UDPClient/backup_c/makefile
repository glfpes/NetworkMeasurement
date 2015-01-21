CFLAGS = -I/home/liaohui/CodeTest/UDPClient/include
SRCS=main.cpp ./source/UDPClinet.cpp
objects=main.o UDPClient.o

main:$(objects)
	g++ -o main $(objects) $(CFLAGS)
run:
	./main
main.o:main.cpp
	g++ -c main.cpp

UDPClient.o:UDPClient.cpp UDPClient.h
	g++ -c UDPClient.cpp

clean:
	rm *.o main

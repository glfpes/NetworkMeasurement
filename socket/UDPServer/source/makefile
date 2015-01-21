CFLAGS = -I/home/liaohui/CodeTest/UDPServer/include
SRCS=main.cpp ./source/UDPServer.cpp
objects=main.o UDPServer.o

main:$(objects)
	g++ -o main $(objects) $(CFLAGS)
run:
	./main
main.o:main.cpp
	g++ -c main.cpp

UDPServer.o:UDPServer.cpp UDPServer.h
	g++ -c UDPServer.cpp

clean:
	rm *.o main

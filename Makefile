CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = node.o host.o link.o link_installer.o service_installer.o message_service_installer.o echo_service.o echo_service_installer.o message_service.o router.o manual_router.o simulator.o object.o

all: first

first: first.o $(OBJECTS)
	$(CC) $(CFLAGS) -o first first.o $(OBJECTS)

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp

host.o: host.cpp host.h
	$(CC) $(CFLAGS) -c host.cpp

link.o : link.cpp link.h
	$(CC) $(CFLAGS) -c link.cpp

link_installer.o: link_installer.cpp link_installer.h
	$(CC) $(CFLAGS) -c link_installer.cpp

service_installer.o : service_installer.cpp service_installer.h
	$(CC) $(CFLAGS) -c service_installer.cpp

message_service_installer.o: message_service_installer.cpp message_service_installer.h
	$(CC) $(CFLAGS) -c message_service_installer.cpp

echo_service.o: echo_service.cpp echo_service.h
	$(CC) $(CFLAGS) -c echo_service.cpp

echo_service_installer.o: echo_service_installer.cpp echo_service_installer.h
	$(CC) $(CFLAGS) -c echo_service_installer.cpp

message_service.o: message_service.cpp message_service.h
	$(CC) $(CFLAGS) -c message_service.cpp

router.o: router.cpp router.h
	$(CC) $(CFLAGS) -c router.cpp

manual_router.o: manual_router.cpp manual_router.h
	$(CC) $(CFLAGS) -c manual_router.cpp

simulator.o : simulator.cpp simulator.h
	$(CC) $(CFLAGS) -c simulator.cpp

object.o : object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp

clean:
	rm -f *.o *.exe first
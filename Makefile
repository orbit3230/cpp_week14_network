CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = node.o host.o link.o link_installer.o service_installer.o message_service_installer.o echo_service.o echo_service_installer.o message_service.o router.o manual_router.o

all: first second third forth

first: first.o $(OBJECTS)
	$(CC) $(CFLAGS) -o first first.o $(OBJECTS)

second: second.o $(OBJECTS)
	$(CC) $(CFLAGS) -o second second.o $(OBJECTS)

third: third.o $(OBJECTS)
	$(CC) $(CFLAGS) -o third third.o $(OBJECTS)

forth: forth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o forth forth.o $(OBJECTS)

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp

third.o: scenarios/third.cpp
	$(CC) $(CFLAGS) -c scenarios/third.cpp

forth.o: scenarios/forth.cpp
	$(CC) $(CFLAGS) -c scenarios/forth.cpp

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

clean:
	rm -f *.o first second third forth
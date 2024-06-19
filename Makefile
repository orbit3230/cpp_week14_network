CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = node.o host.o link.o firewall.o nat.o link_installer.o service_installer.o message_service_installer.o echo_service.o echo_service_installer.o message_service.o bulk_send_service.o bulk_send_service_installer.o packet_sink_service.o packet_sink_service_installer.o router.o manual_router.o auto_router.o simulator.o object.o
OBJECTS_HEADER = node.h packet.h host.h link.h firewall.h nat.h link_installer.h service.h service_installer.h message_service_installer.h echo_service.h echo_service_installer.h message_service.h bulk_send_service.h bulk_send_service_installer.h packet_sink_service.h packet_sink_service_installer.h router.h manual_router.h auto_router.h simulator.h object.h

all: first second third forth fifth sixth

first: first.o $(OBJECTS)
	$(CC) $(CFLAGS) -o first first.o $(OBJECTS)

second: second.o $(OBJECTS)
	$(CC) $(CFLAGS) -o second second.o $(OBJECTS)

third: third.o $(OBJECTS)
	$(CC) $(CFLAGS) -o third third.o $(OBJECTS)

forth: forth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o forth forth.o $(OBJECTS)

fifth: fifth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o fifth fifth.o $(OBJECTS)

sixth: sixth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o sixth sixth.o $(OBJECTS)

first.o: scenarios/first.cpp $(OBJECTS_HEADER)
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp $(OBJECTS_HEADER)
	$(CC) $(CFLAGS) -c scenarios/second.cpp

third.o: scenarios/third.cpp $(OBJECTS_HEADER)
	$(CC) $(CFLAGS) -c scenarios/third.cpp

forth.o: scenarios/forth.cpp $(OBJECTS_HEADER)
	$(CC) $(CFLAGS) -c scenarios/forth.cpp

fifth.o: scenarios/fifth.cpp $(OBJECTS_HEADER)
	$(CC) $(CFLAGS) -c scenarios/fifth.cpp

sixth.o: scenarios/sixth.cpp $(OBJECTS_HEADER)
	$(CC) $(CFLAGS) -c scenarios/sixth.cpp

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp

host.o: host.cpp host.h
	$(CC) $(CFLAGS) -c host.cpp

link.o : link.cpp link.h
	$(CC) $(CFLAGS) -c link.cpp

firewall.o: firewall.cpp firewall.h
	$(CC) $(CFLAGS) -c firewall.cpp

nat.o: nat.cpp nat.h
	$(CC) $(CFLAGS) -c nat.cpp

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

bulk_send_service.o: bulk_send_service.cpp bulk_send_service.h
	$(CC) $(CFLAGS) -c bulk_send_service.cpp

bulk_send_service_installer.o: bulk_send_service_installer.cpp bulk_send_service_installer.h
	$(CC) $(CFLAGS) -c bulk_send_service_installer.cpp

packet_sink_service.o: packet_sink_service.cpp packet_sink_service.h
	$(CC) $(CFLAGS) -c packet_sink_service.cpp

packet_sink_service_installer.o: packet_sink_service_installer.cpp packet_sink_service_installer.h
	$(CC) $(CFLAGS) -c packet_sink_service_installer.cpp

router.o: router.cpp router.h
	$(CC) $(CFLAGS) -c router.cpp

manual_router.o: manual_router.cpp manual_router.h
	$(CC) $(CFLAGS) -c manual_router.cpp

auto_router.o: auto_router.cpp auto_router.h
	$(CC) $(CFLAGS) -c auto_router.cpp

simulator.o : simulator.cpp simulator.h
	$(CC) $(CFLAGS) -c simulator.cpp

object.o : object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp

clean:
	rm -f *.o *.exe first second third forth fifth sixth
#include "router.h"
#include <iostream>

void Router::send(Packet* packet) {
    for (RoutingEntry entry : routingTable_) {
        if (entry.destination == packet->destAddress()) {
            entry.nextLink->transmit(packet);
            std::cout << "Router #" << id() << ": forwarding packet (from: " 
                                            << packet->srcAddress().toString() << ", to: "
                                            << packet->destAddress().toString() << ", " 
                                            << packet->data().size() << " bytes)" << std::endl;
            return;
        }
    }
    std::cout << "Router #" << id() << ": no route for packet (from: " 
                                    << packet->srcAddress().toString() << ", to: "
                                    << packet->destAddress().toString() << ", " 
                                    << packet->data().size() << " bytes)" << std::endl;
}

void Router::receive(Packet* packet) {
    packet_ = packet;
}
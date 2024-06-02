#include "router.h"
#include <iostream>

void Router::send(Packet* packet) {
  for (RoutingEntry entry : routingTable_) {
    if (entry.destination == packet->destAddress()) {
      std::cout << "Router #" << id() << ": forwarding packet (from: " 
                                      << packet->srcAddress().toString() << ", to: "
                                      << packet->destAddress().toString() << ", " 
                                      << packet->data().size() << " bytes)" << std::endl;
      entry.nextLink->transmit(packet, this->id());
      return;
    }
  }
  std::cout << "Router #" << id() << ": no route for packet (from: " 
                                  << packet->srcAddress().toString() << ", to: "
                                  << packet->destAddress().toString() << ", " 
                                  << packet->data().size() << " bytes)" << std::endl;
}

void Router::receive(Packet* packet) {
  // 받아서 적절하게 토스
  send(packet);
}
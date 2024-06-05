#include "router.h"
#include <iostream>

void Router::send() {
  for (RoutingEntry entry : routingTable_) {
    if (entry.destination == packet_->destAddress()) {
      std::cout << "Router #" << id() << ": forwarding packet (from: " 
                                      << packet_->srcAddress().toString() << ", to: "
                                      << packet_->destAddress().toString() << ", " 
                                      << packet_->data().size() << " bytes)" << std::endl;
      entry.nextLink->transmit(packet_, this->id());
      return;
    }
  }
  std::cout << "Router #" << id() << ": no route for packet (from: " 
                                  << packet_->srcAddress().toString() << ", to: "
                                  << packet_->destAddress().toString() << ", " 
                                  << packet_->data().size() << " bytes)" << std::endl;
  unsetPacket();
}

void Router::receive(Packet* packet) {
  setPacket(packet);
  // 받아서 적절하게 토스
  send();
}
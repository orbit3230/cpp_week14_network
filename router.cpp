#include "router.h"
#include "simulator.h"

void Router::send() {
  for (RoutingEntry entry : routingTable_) {
    if (entry.destination == packet_->destAddress()) {
      log("forwarding packet: " + packet_->toString() + " to " + entry.nextLink->toString());
      Simulator::schedule(Simulator::now(), [this, entry]() -> void { entry.nextLink->transmit(packet_, this->id()); });
      return;
    }
  }
  log("no route for packet: " + packet_->toString());
}

void Router::receive(Packet* packet) {
  setPacket(packet);
  // 받아서 적절하게 토스
  send();
}
#include "link.h"
#include "node.h"
#include <iostream>

void Link::transmit(Packet *packet, int fromId) {
  // nodeA_ -> nodeB_ 인 경우
  if (fromId == nodeA_->id()) {
    // debug
    std::cout << "before link schedule A->B" << std::endl;
    Simulator::schedule(Simulator::now(), [this, packet]() { receive(packet, nodeA_); });
    // debug
    std::cout << "after link schedule" << std::endl;
  }
  // nodeB_ -> nodeA_ 인 경우
  else {
    // debug
    std::cout << "before link schedule B->A" << std::endl;
    Simulator::schedule(Simulator::now(), [this, packet]() { receive(packet, nodeB_); });
    // debug
    std::cout << "after link schedule" << std::endl;
  }

}

void Link::send(Packet *packet, Node *to) {
  log("packet out: " + packet->toString() + " to " + to->toString());
  // debug
  std::cout << "before link send schedule" << std::endl;
  Simulator::schedule(Simulator::now(), [this, packet, to]() { to->receive(packet); });
  // debug
  std::cout << "after link send schedule" << std::endl;
}

void Link::receive(Packet *packet, Node *from) {
  log("packet in: " + packet->toString() + " from " + from->toString());
  // debug
  std::cout << "before link receive schedule" << std::endl;
  Simulator::schedule(Simulator::now(), [this, packet, from]() { send(packet, other(from)); });
  // debug
  std::cout << "after link receive schedule" << std::endl;
}
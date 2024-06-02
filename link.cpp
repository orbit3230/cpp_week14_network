#include "link.h"
#include "node.h"
#include <iostream>

void Link::transmit(Packet *packet, int fromId) {
  // nodeA_ -> nodeB_ 인 경우
  if (fromId == nodeA_->id()) {
    std::cout << "Link: forwarding packet from node #" << nodeA_->id()
              << ", to node #" << other(nodeA_)->id() << std::endl;
    other(nodeA_)->receive(packet);
  }
  // nodeB_ -> nodeA_ 인 경우
  else {
    std::cout << "Link: forwarding packet from node #" << nodeB_->id()
              << ", to node #" << other(nodeB_)->id() << std::endl;
    other(nodeB_)->receive(packet);
  }

}
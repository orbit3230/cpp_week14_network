#include "link.h"
#include "node.h"
#include <iostream>

void Link::transmit(Packet *packet) {
  nodeA_->send(packet);
  other(nodeA_)->receive(packet);
  std::cout << "Link: forwarding packet from node #" << nodeA_->id() << " to node #" << other(nodeA_)->id() << std::endl;
}
#include "link.h"
#include "node.h"

void Link::transmit(Packet *packet) {
  nodeA_->send(packet);
  other(nodeA_)->receive(packet);
}
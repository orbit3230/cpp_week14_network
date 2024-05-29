#include "link.h"
#include "node.h"
#include <iostream>

void Link::transmit(Packet *packet) {
  if(true) { // TODO : 과연 패킷을 링크의 어느 방향으로 전달해야 할까?? *^^*
    other(nodeA_)->receive(packet);
  }
  else {
    other(nodeB_)->receive(packet);
  }
  std::cout << "Link: forwarding packet from node #" << nodeA_->id() << " to node #" << other(nodeA_)->id() << std::endl;
}
#include "link.h"
#include "node.h"
#include "simulator.h"

void Link::transmit(Packet *packet, int fromId) {
  // nodeA_ -> nodeB_ 인 경우
  if (fromId == nodeA_->id()) {
    Simulator::schedule(Simulator::now(), [this, packet]() { receive(packet, nodeA_); });
  }
  // nodeB_ -> nodeA_ 인 경우
  else {
    Simulator::schedule(Simulator::now(), [this, packet]() { receive(packet, nodeB_); });
  }

}

void Link::send(Packet *packet, Node *to) {
  log("packet out: " + packet->toString() + " to " + to->toString());
  Simulator::schedule(Simulator::now(), [this, packet, to]() { to->receive(packet); });
}

void Link::receive(Packet *packet, Node *from) {
  log("packet in: " + packet->toString() + " from " + from->toString());
  Simulator::schedule(Simulator::now(), [this, packet, from]() { send(packet, other(from)); });
  from->unsetPacket();
}
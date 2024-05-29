#include "echo_service.h"

void EchoService::send(Packet *packet) {
  host_->send(packet);
}

void EchoService::receive(Packet *packet) {
  std::cout << "EchoService: received "
            << packet->dataString() << " from " << packet->srcAddress().toString() << ":" << packet->srcPort() << ", ";

  std::cout << "send reply with same data" << std::endl;
  host_->send(packet);
}
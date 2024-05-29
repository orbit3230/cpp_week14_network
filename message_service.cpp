#include "message_service.h"
#include <iostream>

void MessageService::send(std::string message) {
  Packet *packet = new Packet(host_->address(), destAddress_, port_, destPort_, message);
  this->send(packet);  // 아래 send 함수 호출
}

void MessageService::send(Packet *packet) {
  host_->send(packet);
}

void MessageService::receive(Packet *packet) {
  std::cout << "MessageService: received"
            << packet->dataString()
            << "from " << packet->srcAddress().toString() << ":" << packet->srcPort() << std::endl;
}
#include "message_service.h"
#include "message_service_installer.h"
#include <iostream>

void MessageService::send(std::string message) {
  Packet *packet = new Packet(host_->address(), destAddress_, port_, destPort_, message);
  host_->setPacket(packet);
  this->send();  // 아래 send 함수 호출
}

void MessageService::send() {
  host_->send();
}

void MessageService::receive(Packet *packet) {
  std::cout << "MessageService: received \""
            << packet->dataString() << "\" "
            << "from " << packet->srcAddress().toString() << ":" << packet->srcPort() << std::endl;

  // MessageService가 패킷을 받으면 시뮬레이션 사이클 종료
  delete packet;
}
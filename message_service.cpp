#include "message_service.h"
#include "message_service_installer.h"

void MessageService::send(std::string message) {
  Packet *packet = new Packet(host_->address(), destAddress_, port_, destPort_, message);
  host_->setPacket(packet);
  this->send();  // 아래 send 함수 호출
}

void MessageService::send() {
  host_->send();
}

void MessageService::receive(Packet *packet) {
  log("received \"" + packet->dataString() + "\" from " 
                    + packet->srcAddress().toString() + ":" + std::to_string(packet->srcPort()));

  // MessageService가 패킷을 받으면 시뮬레이션 사이클 종료
  delete packet;
}
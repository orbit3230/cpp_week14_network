#include "echo_service.h"

void EchoService::send() {
  // 전송자에게 다시 전송
  host_->send();            // 복사본 전송
}

void EchoService::receive(Packet *packet) {
  std::cout << "EchoService: received \""
            << packet->dataString() << "\" "
            << "from " << packet->srcAddress().toString() << ":" << packet->srcPort() << ", ";

  std::cout << "send reply with same data" << std::endl;
  // 받은 패킷을 그대로 전송
  // 방향을 바꾼 패킷을 생성하여 세팅한다.
  Packet *reply = new Packet(packet->destAddress(), packet->srcAddress(), packet->destPort(), packet->srcPort(), packet->data());
  delete packet;            // 원본은 삭제
  host_->unsetPacket();
  host_->setPacket(reply);  // 복사본을 저장
  send();                   // 복사본 전송
}
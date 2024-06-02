#include "echo_service.h"

void EchoService::send(Packet *packet) {
  // 전송자에게 다시 전송
  // host_->send(packet) 은 링크를 랜덤으로 하나 선택하기 때문에
  // 패킷의 방향을 바꾸어 다시 전송해야한다.  
  Packet *reply = new Packet(packet->destAddress(), packet->srcAddress(), packet->destPort(), packet->srcPort(), packet->data());
  delete packet;  // 원본은 삭제
  host_->send(reply);  // 복사본 전송
}

void EchoService::receive(Packet *packet) {
  std::cout << "EchoService: received \""
            << packet->dataString() << "\" "
            << "from " << packet->srcAddress().toString() << ":" << packet->srcPort() << ", ";

  std::cout << "send reply with same data" << std::endl;
  // 받은 패킷을 그대로 전송
  send(packet);
}
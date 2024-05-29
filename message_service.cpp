#include "message_service.h"
#include <iostream>

void MessageService::send(std::string message) {
  Packet *packet = new Packet(host_->address(), destAddress_, port_, destPort_, message);
  // debug
  std::cout << "Packet created\n";
  if(packet == nullptr) {
    std::cout << "packet is nullptr\n";
  }
  else {
    std::cout << "packet is not nullptr\n";
  }
  // 패킷 정보를 출력해보자
  std::cout << "src address: " << packet->srcAddress().toString() << std::endl;
  std::cout << "dest address: " << packet->destAddress().toString() << std::endl;
  std::cout << "src port: " << packet->srcPort() << std::endl;
  std::cout << "dest port: " << packet->destPort() << std::endl;
  std::cout << "message: " << packet->dataString() << std::endl;
  // debug
  if(host_ == nullptr) {
    std::cout << "host_ is nullptr\n";
  }
  else {
    std::cout << "host_ is not nullptr\n";
  }
  // 호스트 정보를 출력해보자
  std::cout << "host address: " << host_->address().toString() << std::endl;
  std::cout << "dest address: " << destAddress_.toString() << std::endl;
  std::cout << "port: " << port_ << std::endl;
  std::cout << "dest port: " << destPort_ << std::endl;
  std::cout << "message: " << message << std::endl;
  this->send(packet);  // 아래 send 함수 호출
}

void MessageService::send(Packet *packet) {
  // debug
  std::cout << "send called\n";
  std::flush(std::cout);
  host_->send(packet);
}

void MessageService::receive(Packet *packet) {
  std::cout << "MessageService: received"
            << packet->dataString()
            << "from " << packet->srcAddress().toString() << ":" << packet->srcPort() << std::endl;
}
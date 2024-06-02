#include "host.h"
#include <iostream>

Host::~Host() {
  for(auto link : links_)
    delete link;
  for(auto service : services_)
    delete service;
}

void Host::initialize() {
}

void Host::send(Packet *packet) {
  std::cout << "Host #" << id() << ": sending packet (from: " 
            << packet->srcAddress().toString() << ", to: "
            << packet->destAddress().toString() << ", " 
            << packet->data().size() << " bytes)" << std::endl;
            
  int random = rand() % links_.size();
  links_[random]->transmit(packet, this->id());
}

void Host::receive(Packet *packet) {
  // 서비스 중 패킷에 맞는 포트를 가진 서비스가 있는 지 확인
  for(auto service : services_) {  // MessageService or EchoService
    if(service->port() == packet->destPort()) {
      std::cout << "Host #" << id() << ": received packet, "
                << "destination port: " << packet->destPort() << std::endl;
      service->receive(packet);
      return;
    }
  }
  // 맞는 포트를 가진 서비스가 없다면
  std::cout << "Host #" << id() << ": no service for packet (from: " 
            << packet->srcAddress().toString() << ", to: "
            << packet->destAddress().toString() << ", " 
            << packet->data().size() << " bytes)" << std::endl;
}
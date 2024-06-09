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

void Host::send() {
  log("sending packet: " + packet_->toString());
            
  int random = rand() % links_.size();
  Simulator::schedule(Simulator::now(), [this, random]() -> void { links_[random]->transmit(packet_, this->id()); });
  unsetPacket();
}

void Host::receive(Packet *packet) {
  // 서비스 중 패킷에 맞는 포트를 가진 서비스가 있는 지 확인
  for(auto service : services_) {  // MessageService or EchoService
    if(service->port() == packet->destPort()) {
      log("received packet: " + packet->toString() + ", forwarding to service: " + service->toString());
      setPacket(packet);
      Simulator::schedule(Simulator::now(), [this, service]() -> void { service->receive(packet_); });
      return;
    }
  }
  // 맞는 포트를 가진 서비스가 없다면
  std::cout << "Host #" << id() << ": no service for packet (from: " 
            << packet->srcAddress().toString() << ", to: "
            << packet->destAddress().toString() << ", " 
            << packet->data().size() << " bytes)" << std::endl;
}
#include "host.h"
#include "simulator.h"

Host::~Host() {
  for(auto link : links_)
    delete link;
  for(auto service : services_)
    delete service;
}

void Host::initialize() {
  for(auto service : services_)
    service->initialize();
}

void Host::send() {
  log("sending packet: " + packet_->toString());
            
  int random = rand() % links_.size();
  links_[random]->transmit(packet_, this->id());
}

void Host::receive(Packet *packet) {
  // 서비스 중 패킷에 맞는 포트를 가진 서비스가 있는 지 확인
  for(auto service : services_) {  // MessageService or EchoService or BulkSendService or PacketSinkService
    if(service->port() == packet->destPort()) {
      log("received packet: " + packet->toString() + ", forwarding to " + service->toString());
      setPacket(packet);
      service->receive(packet_);
      return;
    }
  }
  // 맞는 포트를 가진 서비스가 없다면
  log("no service for packet: " + packet->toString());
}
#include "host.h"
#include <iostream>

void Host::initialize() {
  for(size_t i = 0; i < services_.size(); i++) {
    delete services_[i];
  }
}

void Host::send(Packet *packet) {
  int random = rand() % links_.size();
  links_[random]->transmit(packet);
  std::cout << "Host #" << id() << ": sending packet (from: " 
            << packet->srcAddress().toString() << ", to: "
            << packet->destAddress().toString() << ", " 
            << packet->data().size() << " bytes)" << std::endl;
}

void Host::receive(Packet *packet) {
  packet_ = packet;
  std::cout << "Host #" << id() << ": received packet (from: " 
            << packet->srcAddress().toString() << ", to: "
            << packet->destAddress().toString() << ", " 
            << packet->data().size() << " bytes)" << std::endl;
  for(size_t i = 0; i < services_.size(); i++) {
    services_[i]->receive(packet);
  }
}
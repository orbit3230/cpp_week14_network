#include "host.h"

void Host::initialize() {
  for(int i = 0; i < services_.size(); i++) {
    delete services_[i];
  }
}

void Host::send(Packet *packet) {
  int random = rand() % services_.size();
}
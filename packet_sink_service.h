#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
  friend class PacketSinkServiceInstaller;
private:
  PacketSinkService(Host *host, short port);

  void send() override;
  void receive(Packet *packet) override;
};

#endif
#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
  friend class PacketSinkServiceInstaller;
private:
  PacketSinkService(Host *host, short port);

  // 서비스를 초기화한다
  void initialize() override;

  std::string name() override { return "PacketSinkService"; }

  int receivedBytes_ = 0;

  void send() override;
  void receive(Packet *packet) override;
};

#endif
#include "packet_sink_service.h"

PacketSinkService::PacketSinkService(Host *host, short port) : Service(host, port) {}

void PacketSinkService::send() {
  // nothing
}

void PacketSinkService::receive(Packet *packet) {
  int packetSize = packet->data().size();
  log("received total " + std::to_string(packetSize) + " bytes");
}
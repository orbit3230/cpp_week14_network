#include "packet_sink_service.h"

PacketSinkService::PacketSinkService(Host *host, short port) : Service(host, port) {}

void PacketSinkService::initialize() {
  // nothing
}

void PacketSinkService::send() {
  // nothing
}

void PacketSinkService::receive(Packet *packet) {
  receivedBytes_ += packet->data().size();
  log("received total " + std::to_string(receivedBytes_) + " bytes");
}
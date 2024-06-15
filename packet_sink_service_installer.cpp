#include "packet_sink_service_installer.h"

PacketSinkService *PacketSinkServiceInstaller::install(Host *host, short port_) {
  PacketSinkService *packetSinkService = new PacketSinkService(host, port_);
  ServiceInstaller::install(host, packetSinkService);
  return packetSinkService;
}
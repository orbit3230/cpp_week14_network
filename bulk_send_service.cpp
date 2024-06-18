#include "bulk_send_service.h"

BulkSendService::BulkSendService(Host *host, Address destination, short destPort, double delay, double startTime, double stopTime)
    : Service(host, 0), destAddress_(destination), destPort_(destPort), delay_(delay), startTime_(startTime), stopTime_(stopTime) {
}

void BulkSendService::send() {
  for(double currentTime = startTime_; currentTime < stopTime_; currentTime += delay_) {
    // make packet data of PACKET_SIZE
    std::string data = "";
    for (int i = 0; i < PACKET_SIZE; i++) {
      data += "A";
    }

    Packet *packet = new Packet(host_->address(), destAddress_, port_, destPort_, data);
    Simulator::schedule(currentTime, [this, packet]() {
      log("sending data");
      host_->setPacket(packet);
      host_->send();
    });
  }
}

void BulkSendService::receive(Packet *packet) {
  // nothing
}
#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H

#include "host.h"
#include "service.h"
#include "simulator.h"

#define PACKET_SIZE 512

class BulkSendService : Service {
  friend class BulkSendServiceInstaller;

private:
  Address destAddress_;
  short destPort_;
  double delay_;
  double startTime_;
  double stopTime_;

  BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0);

  std::string name() override { return "BulkSendService"; }
  
  void send() override;
  void receive(Packet *packet) override;
};

#endif
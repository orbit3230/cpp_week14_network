#ifndef ECHO_SERVICE_H
#define ECHO_SERVICE_H

#include "host.h"
#include "service.h"
#include <string>

// 수신한 패킷을 전송자에게 다시 전송하는 서비스
class EchoService : public Service {
  friend class EchoServiceInstaller;

private:
  EchoService(Host *host, short port) : Service(host, port) {}

  std::string name() override { return "EchoService"; }

public:
  // 서비스를 초기화한다
  void initialize() override;
  // 패킷을 전송한다
  void send() override;
  // 패킷을 수신한다
  void receive(Packet *packet) override;
};

#endif
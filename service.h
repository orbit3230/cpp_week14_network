#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"

class Host;

class Service {
  friend class ServiceInstaller;

protected:
  // 서비스가 설치된 호스트
  Host *host_;

  // 서비스가 사용하는 포트
  short port_;

  Service(Host *host, short port) : host_(host), port_(port) {}

public:
  virtual ~Service() {}
  short port() const { return port_; }
  // 패킷을 전송
  virtual void send() = 0;
  // 패킷을 수신
  virtual void receive(Packet *packet) = 0;
};

#endif
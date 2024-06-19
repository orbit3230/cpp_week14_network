#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"

class Host;

class Service : public Object {
  friend class ServiceInstaller;

private :
  virtual std::string name() override { return "Service"; }

protected:
  // 서비스가 설치된 호스트
  Host *host_;

  // 서비스가 사용하는 포트
  short port_;

  Service(Host *host, short port) : host_(host), port_(port) {}

public:
  virtual ~Service() {}
  virtual void initialize() = 0;
  short port() const { return port_; }
  virtual void send() = 0;
  virtual void receive(Packet *packet) = 0;
};

#endif
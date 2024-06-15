#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;

  RoutingEntry(Address destination, Link *nextLink) : destination(destination), nextLink(nextLink) {}
};

class Router : public Node {
private :
  virtual std::string name() override { return "Router"; }

protected:
  std::vector<RoutingEntry> routingTable_;

public:
  virtual ~Router() {}
  
  // 패킷의 목적지 address를 확인하여 적절한 링크를 찾아 전송
  void send() override;
  // 패킷을 수신하여 알맞은 곳으로 전달(send 호출)
  void receive(Packet *packet) override;
};

#endif
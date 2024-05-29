#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>

class Node {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

protected:
  Packet *packet_;
  std::vector<Link *> links_;

public:
  Node() : id_(nextId_++) {}
  virtual ~Node() {}
  int id() const { return id_; }

  // 노드가 패킷을 수신 - virtual
  virtual void receive(Packet *packet) = 0;
  // 노드가 패킷을 전송 - virtual
  virtual void send(Packet *packet) = 0;
};

#endif
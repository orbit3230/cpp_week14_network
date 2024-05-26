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

public:
  Node() : id_(nextId_++) {}
  int id() const { return id_; }

  // 노드가 패킷을 수신
  void receive(Packet *packet);
  // 노드가 패킷을 전송
  void send(Packet *packet);
};

#endif
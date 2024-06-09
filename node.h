#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "object.h"
#include "packet.h"
#include <vector>

class Node : public Object {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

  virtual std::string name() override { return "Node"; }

protected:
  Packet *packet_;
  // 노드에 연결된 링크 목록
  std::vector<Link *> links_;

public:
  Node() : id_(nextId_++) {}
  virtual ~Node() {}
  int id() const { return id_; }

  // 노드에 패킷을 설정
  void setPacket(Packet *packet) { packet_ = packet; }
  // 노드에 패킷을 해제
  void unsetPacket() { packet_ = nullptr; }

  // 노드가 패킷을 전송 - virtual
  virtual void send() = 0;
  // 노드가 패킷을 수신 - virtual
  virtual void receive(Packet *packet) = 0;
};

#endif
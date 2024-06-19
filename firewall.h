#include "address.h"
#include "node.h"
#include "object.h"
#include <set>
#include <string>

class FirewallPolicy : public Object {
private:
  std::string name() override { return "FirewallPolicy"; }
public:
  virtual bool isAllowed(Packet* packet) = 0;
};

class Firewall : public Node {
private:
  class AllowAnyPolicy : public FirewallPolicy {
  private:
    short destPort_;
    std::string name() override { return "AllowAnyPolicy"; }

  public:
    AllowAnyPolicy(short destPort) : destPort_(destPort) {}
    bool isAllowed(Packet* packet) override;
  };

  class AllowSpecificPolicy : public FirewallPolicy {
  private:
    Address srcAddress_;
    short destPort_;
    std::string name() override { return "AllowSpecificPolicy"; }

  public:
    AllowSpecificPolicy(Address srcAddress, short destPort)
        : srcAddress_(srcAddress), destPort_(destPort) {}
    bool isAllowed(Packet* packet) override;
  };

  Link *receiveLink_ = nullptr;
  std::vector<FirewallPolicy*> policies_;

  std::string name() override { return "Firewall"; }

public:
  void setReceiveLink(Link *link) { receiveLink_ = link; }

  void addAllowAnyPolicy(short destPort);
  void addAllowSpecificPolicy(Address srcAddress, short destPort);

  void send() override;
  void receive(Packet *packet) override;
};
#include "address.h"
#include "host.h"
#include "link.h"
#include <set>
#include <vector>

struct NatEntry {
  Address internalAddress;
  short internalPort;
  short externalPort;
};

class Nat : public Node {
private:
  Address address_;

  Link *wanLink_;
  std::vector<NatEntry> natTable_;

  std::string name() override { return "Nat"; }

  int lastPort_ = 1000;
  // Internet -> LAN
  Packet *convertInternetToLanPacket();
  // LAN -> Internet
  Packet *convertLanPacketToInternetPacket();
  // 새로운 포트 번호를 생성
  int getNewPort();
  // NAT 테이블에 새로운 엔트리를 추가
  NatEntry* addNatEntry();
  // 연결이 처음 생기는 경우인지 확인
  bool isFirst();
  // 존재하는 NAT 엔트리를 탐색
  NatEntry* findExistingNatEntry();

public:
  Nat(Address address) : address_(address) {}
  Address address() { return address_; }
  void setWanLink(Link *link) { wanLink_ = link; }

  void send() override;
  void receive(Packet *packet) override;
};

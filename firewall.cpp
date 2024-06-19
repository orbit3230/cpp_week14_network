#include "firewall.h"
#include <vector>
#include "host.h"
#include <iostream>

// --FirewallPolicy public--
bool Firewall::AllowAnyPolicy::isAllowed(Packet *packet) {
  return packet->destPort() == destPort_;
}
// --FirewallPolicy public--
bool Firewall::AllowSpecificPolicy::isAllowed(Packet *packet) {
  return packet->srcAddress() == srcAddress_ && packet->destPort() == destPort_;
}

// --Firewall public--
void Firewall::addAllowAnyPolicy(short destPort) {
  policies_.push_back(new AllowAnyPolicy(destPort));
}
void Firewall::addAllowSpecificPolicy(Address srcAddress, short destPort) {
  policies_.push_back(new AllowSpecificPolicy(srcAddress, destPort));
}

void Firewall::send() {
  std::vector<Link*> links = this->links();
  // receiveLink_와 다른, 즉 패킷이 온 방향이 아닌 다른 방향의 링크를 찾아서 전송하자.  
  for(Link* link : links) {
    if(link != receiveLink_) {
      link->transmit(packet_, this->id());
    }
  }
  unsetPacket();
  // 성공했다면 따로 로그를 남기지는 않음
  // 실제로도 방화벽이 통과시킬 때마다 로그를 계속 알려준다면 굉장히 짜증나지 않을까
}

void Firewall::receive(Packet *packet) {
  // receiveLink_로 부터 온 패킷인지 확인해야하는데... 현재 상황으로는 어렵다..
  // 패킷이 들어온 방향(링크)를 알 수가 없다..
  // 그래서 어쩔수없지만.. 패킷이 향하는 방향이 현재 호스트인지 확인해보자..
  // 다만 방화벽이 호스트와 직접 연결되어 있다는 가정하에..
  std::vector<Link*> links = this->links();
  std::vector<Address> addresses;
  for(Link* link : links) {
    if(link->a() == this) {
      Host* host = dynamic_cast<Host*>(link->b());
      if(host != nullptr) {
        addresses.push_back(host->address());
      } 
    }
    else {
      Host* host = dynamic_cast<Host*>(link->a());
      if(host != nullptr) {
        addresses.push_back(host->address());
      }
    }
  }

  bool isForwardingHost = false;
  for(Address address : addresses) {
    if(packet->destAddress() == address) {
      isForwardingHost = true;
      break;
    }
  }

  // 호스트로 향하는 패킷이라면 방화벽 정책을 확인하고 전송
  if(isForwardingHost) {
    setPacket(packet);
    for(FirewallPolicy* policy : policies_) {
        if(policy->isAllowed(packet)) {
        send();
        return;
        }
    }

    log("Dropping " + packet->toString() 
                    + " with src address " + packet->srcAddress().toString() 
                    + " and dest port " + std::to_string(packet->destPort()));
    unsetPacket();
  }
  // 호스트로 향하는게 아니라면 일반적인 전송으로 처리
  else {
    receiveLink_->transmit(packet, this->id());
  }
}
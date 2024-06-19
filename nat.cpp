#include "nat.h"

// --private--
Packet* Nat::convertInternetToLanPacket() {
  NatEntry* entry;
  if(isFirst()) {  // 연결이 처음 생기는 경우
    entry = addNatEntry();
  }
  else { // 연결이 이미 존재하는 경우
    entry = findExistingNatEntry();
  }
  Packet* newPacket = new Packet(
    packet_->srcAddress(),
    entry->internalAddress,
    packet_->srcPort(),
    entry->internalPort,
    packet_->dataString()
  );
  unsetPacket();
  setPacket(newPacket);
  return newPacket;
}
Packet* Nat::convertLanPacketToInternetPacket() {
  NatEntry* entry;
  if(isFirst()) {  // 연결이 처음 생기는 경우
    entry = addNatEntry();
  }
  else { // 연결이 이미 존재하는 경우
    entry = findExistingNatEntry();
  }

  Packet* newPacket = new Packet(
    address_,
    packet_->destAddress(),
    entry->externalPort,
    packet_->destPort(),
    packet_->dataString()
  );
  unsetPacket();
  setPacket(newPacket);
  return newPacket;
}
  
int Nat::getNewPort() {
  return lastPort_++;
}

NatEntry* Nat::addNatEntry() {
  int natPort = getNewPort();
  NatEntry* entry = new NatEntry;
  entry->internalAddress = packet_->srcAddress();
  entry->internalPort = packet_->srcPort();
  entry->externalPort = natPort;
  natTable_.push_back(*entry);

  return entry;
}

bool Nat::isFirst() {
  for(NatEntry entry : natTable_) {
    if(entry.externalPort == packet_->destPort()) {
      return false;
    }
  }
  return true;
}

NatEntry* Nat::findExistingNatEntry() {
  for(NatEntry& entry : natTable_) {
    if(entry.externalPort == packet_->destPort()) {
      return &entry;
    }
  }
  return nullptr;  // 만약 프로그램이 비정상 종료된다면 원인이 될 수도 있는 부분
}

// --public--
void Nat::send() {
  // 도착지가 현재 자신의 주소라면, 이제 도착한 것임. 따라서 LAN으로 전송
  if(packet_->destAddress() == address_) {
    convertInternetToLanPacket();
    // LAN link들 모두에게 전송
    std::vector<Link*> links = this->links();
    for(Link* link : links) {
      Host* host = dynamic_cast<Host*>(link->other(this));
      if(host != nullptr) {
        link->transmit(packet_, this->id());
      }
    }
  }
  // 도착지가 자신의 주소가 아니라면, 이제 출발하는 것. 따라서 인터넷으로 전송
  else {
    convertLanPacketToInternetPacket();
    wanLink_->transmit(packet_, this->id());
  }
}

void Nat::receive(Packet* packet) {
  setPacket(packet);
  send();
}
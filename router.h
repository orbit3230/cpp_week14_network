#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;

  RoutingEntry(Address destination, Link *nextLink) : destination(destination), nextLink(nextLink) {}
};

class Router : public Node {
protected:
  std::vector<RoutingEntry> routingTable_;
};

#endif
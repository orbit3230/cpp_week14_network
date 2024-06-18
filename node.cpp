#include "node.h"

int Node::nextId_ = 0;

Link *Node::linkTo(Node *node) {
  for (Link *link : links_) {
    // 주소를 비교 (because '==' operator not defined)
    if (link->a() == node || link->b() == node) {
      return link;
    }
  }
  return nullptr;
}
#include "link_installer.h"

Link *LinkInstaller::install(Node *a, Node *b) {
  Link *link = new Link(a, b);
  a->links_.push_back(link);
  b->links_.push_back(link);
  return link;
}
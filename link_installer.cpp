#include <link_installer.h>

Link *LinkInstaller::install(Node *a, Node *b) {
  return new Link(a, b);
}
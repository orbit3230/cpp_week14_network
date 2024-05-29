#include "service_installer.h"
#include <iostream>

void ServiceInstaller::install(Host *host, Service *service) {
  // debug
  std::cout << "ServiceInstaller::install() called\n";
  service->host_ = host;
  std::cout << "ServiceInstaller::install() host_ is set\n";
  std::cout << host->address().toString() << std::endl;
  host->services_.push_back(service);
}
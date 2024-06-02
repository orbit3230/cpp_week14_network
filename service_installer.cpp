#include "service_installer.h"

void ServiceInstaller::install(Host *host, Service *service) {
  service->host_ = host;
  host->services_.push_back(service);
}

short ServiceInstaller::availablePort(Host *host) {
  short port = 1000;
  for(auto service : host->services_)
    if(service->port() == port)
      port++;
  return port;
}
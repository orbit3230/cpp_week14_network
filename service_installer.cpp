#include "service_installer.h"

void ServiceInstaller::install(Host *host, Service *service) {
  service->host_ = host;
  host->services_.push_back(service);
}
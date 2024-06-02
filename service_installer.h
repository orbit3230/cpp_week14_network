#ifndef SERVICE_INSTALLER_H
#define SERVICE_INSTALLER_H

#include "host.h"
#include "service.h"

// 서비스를 설치하는 역할
class ServiceInstaller {
protected:
  // 호스트와 서비스 사이의 관계를 설정한다.
  void install(Host *host, Service *service);

  // 호스트에 사용 가능한 포트번호를 찾아주는 메소드 (from 1000)
  short availablePort(Host *host);
};

#endif
#include "message_service_installer.h"

MessageService *MessageServiceInstaller::install(Host *host) {
  // 포트 번호는 1000부터 시작하여 이미 사용 중인 포트라면 1씩 증가
  short port = availablePort(host);
  MessageService *messageService = new MessageService(host, port, destAddress_, destPort_);
  ServiceInstaller::install(host, messageService);
  return messageService;
}
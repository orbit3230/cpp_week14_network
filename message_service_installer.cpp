#include "message_service_installer.h"

MessageService *MessageServiceInstaller::install(Host *host) {
  // TODO : port_를 1000이 아닌 무엇으로
  MessageService *messageService = new MessageService(host, 1000, destAddress_, destPort_);
  ServiceInstaller::install(host, messageService);
  return messageService;
}
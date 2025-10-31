#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
  int client_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (client_sock == -1) handle_error("client sock"); 

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);

  inet_aton("127.0.0.1", (struct in_addr *) &(addr.sin_addr.s_addr));

  connect(client_sock, (struct sockaddr *) &addr, sizeof(addr));

  char serv_message[256];
  char cli_message[] = "Hello from client";
  memset(serv_message, 0, 256);
  recv(client_sock, serv_message, 255, 0);
  

  send(client_sock, cli_message, strlen(cli_message), 0);

  if (close(client_sock) == -1) handle_error("close");

  printf("%s", serv_message);
  return 0;
}

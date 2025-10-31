#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAX_QUEUE_SIZE 10
#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
  int host_sock = socket(AF_INET, SOCK_STREAM, 0);
  int client_sock;
  socklen_t client_addr_size;
  if (host_sock == -1) handle_error("socket");
  

  struct sockaddr_in addr, client_addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(host_sock, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    handle_error("bind");
  }

  if (listen(host_sock, MAX_QUEUE_SIZE) == -1) {
    handle_error("listen");
  }
  
  client_addr_size = sizeof(client_addr);
  client_sock = accept(host_sock, (struct sockaddr *) &client_addr, &client_addr_size);

  if (client_sock == -1) handle_error("accept");

  char message[] = "Hello from server";
  send(client_sock, message, strlen(message), 0);
  char cli_message[256];
  memset(&cli_message, 0, 256);

  recv(client_sock, cli_message, 255, 0);
  
  if (close(host_sock) == -1) handle_error("close");

  printf("%s", cli_message);
}

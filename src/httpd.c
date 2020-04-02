#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define LISTEN_PORT 8123

void err(char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  char *http_response = "HTTP/1.1 200 OK\r\n\r\n"
    "<html><head><title>Hello World</title><body>Hello World</body></html>\n";

  int sockfd = 0;
  int clisockfd = 0;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    err("socket() error");
  }

  struct sockaddr_in sockaddr = {};
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_port = htons(LISTEN_PORT);
  sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sockfd, (struct sockaddr *) &sockaddr, sizeof(sockaddr)) < 0) {
    err("bind() error");
  }

  if (listen(sockfd, 5) < 0) {
    err("listen() error");
  } else {
    printf("Listening on 0.0.0.0:%d...\n", LISTEN_PORT);
  }

  while (1) {
    if ((clisockfd = accept(sockfd, NULL, NULL)) < 0) {
      err("accept() error");
    }

    char buf[30000] = {0};
    read(clisockfd, buf, sizeof(buf));
    printf("%s\n", buf);

    write(clisockfd, http_response, strlen(http_response));

    close(clisockfd);
  }

  exit(EXIT_SUCCESS);
}

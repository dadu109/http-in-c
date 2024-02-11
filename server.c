#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_MESSAGE_LENGTH 1024

void handle_connection(int connfd) {
  char buff[MAX_MESSAGE_LENGTH];
  bzero(buff, MAX_MESSAGE_LENGTH);

  read(connfd, buff, sizeof(buff));
  printf("From client: %s", buff);
}

void start_server(int port, int connection_backlog_count) {
  struct sockaddr_in dest; /* socket info about the machine connecting to us */
  struct sockaddr_in serv; /* socket info about our server */
  int mysocket;            /* socket used to listen for incoming connections */
  socklen_t socksize = sizeof(struct sockaddr_in);

  memset(&serv, 0,
         sizeof(serv));      /* zero the struct before filling the fields */
  serv.sin_family = AF_INET; /* set the type of connection to TCP/IP */
  serv.sin_addr.s_addr =
      htonl(INADDR_ANY);       /* set our address to any interface */
  serv.sin_port = htons(port); /* set the server port number */

  mysocket = socket(AF_INET, SOCK_STREAM, 0);

  /* bind serv information to mysocket */
  bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

  /* start listening, allowing a queue of up to 1 pending connection */
  listen(mysocket, connection_backlog_count);
  int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);

  handle_connection(consocket);

  close(mysocket);
}

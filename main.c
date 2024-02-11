#include "server.h"
#include <stdlib.h>

#define PORT 80
#define MAX_ACTIVE_CONNECTIONS 1

int main() {
  start_server(PORT, MAX_ACTIVE_CONNECTIONS);

  return EXIT_SUCCESS;
}

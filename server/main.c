#include "includes/server.h"

int main() {
    t_server *server = create_server();

    if (server == NULL)
        my_printf("Failed to start server\n");
    else
      server->start();
    return 0;
}

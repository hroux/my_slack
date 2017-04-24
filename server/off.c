#include "includes/server.h"
#include <stdlib.h>

void terminate(t_server *server) {

    server->clients->free(server->clients);
    server->rooms->free(server->rooms);
    server->protocol = NULL;
    server->clients = NULL;
    server->rooms = NULL;
    free(server);
}

void free_client(void *arg) {
    t_client *c = (t_client *)arg;

    free(c);
}

void free_room(void *arg) {
    t_room *r = (t_room *)arg;

    r->clients->free(r->clients);
    free(r->name);
    free(r);
}
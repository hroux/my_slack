#include "includes/server.h"
#include <string.h>

int main() {
    t_server *server = create_server();

    if (server == NULL)
        my_printf("Failed to start server\n");
    else
      server->start(server);
    return 0;
    // TEST FREE ROOMS
//    t_list *rooms = create_list(sizeof(t_room), free_room);
//    t_room *r =  create_room(strdup("general"), 1);
//
//    rooms->push(rooms, r);
//    rooms->free(rooms);
//
////    free(r->name);
//    free(r);

//    return 0;

    // TEST FREE CLIENTS
//    t_list *clients = create_list(sizeof(t_client), free_client);
//    t_client *c = malloc(sizeof(t_client));
//
//    c->name = strdup("Filip");
//    c->socket = 1;
//
//    clients->push(clients, c);
//    clients->free(clients);
//
////    free(c->name);
//    free(c);
//
//    return 0;
}

#include "includes/server.h"

void    on_user_disconnected(t_server *server, t_client *client) {
    t_list_item *node;

    node = server->clients->find(server->clients, client);
    if (node == NULL)
        return;

    client->room->remove_client(client->room, client);
    server->clients->remove_at(server->clients, node->index);
}
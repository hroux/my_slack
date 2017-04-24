#include "includes/server.h"
#include <string.h>

void    show_rooms_cmd(t_server *server, char *something, t_client *client) {
    t_list_item *room_node;
    t_room *r;
    char msg[MSG_LENGTH];

    room_node = server->rooms->head;
    send(client->socket, "Liste des salons : \n", strlen("Liste des salons : \n"), 0);
    while (room_node != NULL) {
        r = (t_room *) room_node->data;
        sprintf(msg, "#%s\n", r->name);
        send(client->socket, msg, strlen(msg), 0);
        room_node = room_node->next;
    }

    if (something != NULL) {
        my_printf("Why do you pass this => %s ??", something);
    }
}

void    join_room_cmd(t_server *server, char *room_name, t_client *client) {
    t_room *next;
    char err_msg[MSG_LENGTH];

    if (room_name == NULL || strlen(room_name) < 1) {
        sprintf(err_msg, "Le nom du salon ne doit pas etre vide !\n");
        send(client->socket, err_msg, my_strlen(err_msg), 0);
        return;
    }

    next = get_room_by_name(server->rooms, room_name);
    if (next == NULL) {
        sprintf(err_msg, "Le salon %s n'existe pas !\n", room_name);
        send(client->socket, err_msg, my_strlen(err_msg), 0);
        return;
    }
    my_printf("next name : %s\n", next->name);
    my_printf("client->room->name : %s\n", client->room->name);
    if (strcmp(next->name, client->room->name) == 0)
        return;

    client->room->remove_client(client->room, client);
    next->add_client(next, client);
}

void    create_room_cmd(t_server *server, char *room_name, t_client *client) {
    t_room *new;

    new = create_room(room_name, 0);
    server->rooms->push(server->rooms, new);
    join_room_cmd(server, room_name, client);
}

void    delete_room_cmd(t_server *server, char *room_name, t_client *client) {
    t_room *to_delete;
    t_list_item *client_node;
    t_client *c;
    char err_msg[MSG_LENGTH];

    to_delete = get_room_by_name(server->rooms, room_name);
    if (to_delete == NULL) {
        sprintf(err_msg, "Le salon %s n'existe pas !\n", room_name);
        send(client->socket, err_msg, my_strlen(err_msg), 0);
        return;
    }

    if (to_delete->permanent) {
        sprintf(err_msg, "Le salon %s ne peut pas etre supprimé !\n", room_name);
        send(client->socket, err_msg, my_strlen(err_msg), 0);
        return;
    }

    client_node = to_delete->clients->head;
    while (client_node != NULL) {
        c = (t_client *) client_node->data;
        join_room_cmd(server, "general", c);
        client_node = (t_list_item *)client_node->next;
    }

    server->rooms->remove(server->rooms, get_room_node(server->rooms, to_delete), TRUE);
}

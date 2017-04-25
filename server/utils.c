#include "includes/server.h"
#include <stdlib.h>
#include <string.h>

t_list_item *get_client_node(t_list *clients, t_client *client) {
    t_list_item *tmp;
    t_client *c;

    tmp = clients->head;
    while (tmp != NULL) {
        c = (t_client *)tmp->data;
        if (strcmp(c->name, client->name) == 0)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

t_list_item *get_room_node(t_list *rooms, t_room *room) {
    t_list_item *tmp;
    t_room *r;

    tmp = rooms->head;
    while (tmp != NULL) {
        r = (t_room *)tmp->data;
        if (strcmp(r->name, room->name) == 0)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

t_room *get_room_by_name(t_list *rooms, char *name) {
    t_list_item *tmp;
    t_room *r;

    tmp = rooms->head;
    while (tmp != NULL) {
        r = (t_room *)tmp->data;
        if (strcmp(r->name, name) == 0)
            return tmp->data;
        tmp = tmp->next;
    }

    return NULL;
}


/**
 * Un str_replace normal
 */
void my_str_replace(char *str, char find, char replace) {
    int i;

    i = 0;
    if (str == NULL)
        return;
    while (str[i] != '\0') {
        if (str[i] == find)
            str[i] = replace;
        i++;
    }
}

/*
** main.c for my_slack in /home/camille/slack/my_slack/server
**
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
**
** Started on  Wed Apr 26 15:05:12 2017 VRIGNAUD camille
** Last update Wed Apr 26 15:06:27 2017 VRIGNAUD camille
*/

#include "includes/server.h"
#include <string.h>

int		main() {
t_server	*server = create_server();

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

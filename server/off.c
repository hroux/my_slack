/*
** off.c for my_slack in /home/camille/slack/my_slack/server
**
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
**
** Started on  Wed Apr 26 15:08:12 2017 VRIGNAUD camille
** Last update Wed Apr 26 15:08:56 2017 VRIGNAUD camille
*/

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

void		free_client(void *arg) {
  t_client	*c = (t_client *)arg;

  free(c);
}

void		free_room(void *arg) {
  t_room	*r = (t_room *)arg;

  r->clients->free(r->clients);
  free(r->name);
  free(r);
}

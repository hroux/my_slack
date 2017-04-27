#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

void  fill_bind_client(t_client *new_client, char *buffer,
   t_room *general, t_server *this)
{
  int n;
  char		connect_msg[64];

  n = recv(new_client->socket, buffer, sizeof(buffer), 0);
  send_callback_msg(new_client->socket);
  buffer[n - 1] = '\0';
  new_client->name = my_strdup(buffer);
  new_client->room = general;
  general->add_client(general, new_client);
  my_printf("Created new client with id => %d\n", new_client->socket);
  sprintf(connect_msg, "User %s connected\n", new_client->name);
  this->clients->push(this->clients, new_client);
  broadcast_msg(this, connect_msg);
}

int		bind_client(void *server, void *node) {
  t_client	*c;
  t_server	*s;

  c = (t_client *) ((t_list_item *) node)->data;
  s = (t_server *) server;
  FD_SET(c->socket, &s->readfs);
  return (1);
}

#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

void		create_client(t_server *this) {
  t_room	*general;
  t_client	*new_client;
  char		buffer[32];

  general = (t_room *) this->rooms->head->data;
  new_client = malloc(sizeof(t_client));
  if (new_client == NULL)
    return;
  new_client->name = NULL;
  new_client->socket = accept(this->listener, (struct sockaddr *) &this->cli, &this->socklen);
  if (new_client->socket < 0)
    {
      free(new_client);
      return;
    }
  send(new_client->socket, "Welcome|to|my|slack|!\n",
       my_strlen("Welcome|to|my|slack|!\n"), 0);
  get_callback_msg(new_client->socket);
  send(new_client->socket, "Enter|your|name|:|",
       my_strlen("Enter|your|name|:|"), 0);
  get_callback_msg(new_client->socket);
  fill_bind_client(new_client, buffer, general, this);
  free(new_client);
}

void fill_on_client(char *buffer, t_client *c, t_server *s, int n)
{
  buffer[n] = '\0';
  my_printf("Message => %s\n", buffer);
  send_callback_msg(c->socket);
  handle_message(s, buffer, c);
  FD_CLR(c->socket, &s->readfs);
}

int		on_client_message(void *server, void *node) {
  char		buffer[MSG_LENGTH];
  char		deco_msg[128];
  int		n;
  t_server	*s;
  t_client	*c;

  s = (t_server *) server;
  c = (t_client *) ((t_list_item *) node)->data;
  if (FD_ISSET(c->socket, &s->readfs)) {
    my_printf("Message from %s\n", c->name);
    n = recv(c->socket, buffer, sizeof(buffer), 0);
    if (n == 0 || n == -1)
      {
	my_printf("User %s disconnected\n", c->name);
	sprintf(deco_msg, "User %s disconnected\n", c->name);
	close(c->socket);
	c->room->remove_client(c->room, c);
	s->clients->remove(s->clients, get_client_node(s->clients, c), 1);
	broadcast_msg(s, deco_msg);
	return (1);
      }
   fill_on_client(buffer, c, s, n);
  }
  return (1);
}

/*
** server.c for my_slack in /home/camille/slack/my_slack/server
**
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
**
** Started on  Wed Apr 26 15:12:50 2017 VRIGNAUD camille
** Last update Wed Apr 26 19:07:01 2017 VRIGNAUD camille
*/

#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

t_server	*create_server() {
  t_server	*server;

  server = malloc(sizeof(t_server));
  if (server == NULL)
    return (NULL);
  server->socklen = sizeof(server->addr);
  server->protocol = getprotobyname(PROTOCOL);
  if (server->protocol == NULL)
      return NULL;
  server->listener = socket(AF_INET, SOCK_STREAM, server->protocol->p_proto);
  if (server->listener == -1)
      return NULL;
  fill_server(server);
  if (bind(server->listener, (const struct sockaddr *) &server->addr,
	   sizeof(server->addr)) == -1)
      return (NULL);
  if (listen(server->listener, BACKLOG) == -1)
      return (NULL);
  server_init(server);
  return (server);
}

void		server_init(t_server *this) {
  t_room	*general;

  this->rooms = create_list(sizeof(t_room), free_room);
  this->clients = create_list(sizeof(t_client), free_client);
  this->start = start_server;
  this->terminate = terminate;
  this->broadcast = broadcast_msg;
  general = create_room(my_strdup("general"), TRUE);
  this->rooms->push(this->rooms, general);
  free(general);
}


int	start_server(t_server *this) {
  int	fds;

  my_printf("Slack server started successfully !\n");
  while (1) {
    FD_ZERO(&this->readfs);
    FD_SET(0, &this->readfs);
    FD_SET(this->listener, &this->readfs);
    this->clients->for_each(this->clients, bind_client, this);
    my_printf("Number of clients => %d\n", this->clients->size);
    fds = select(4 + this->clients->size, &this->readfs, NULL, NULL, NULL);
    my_printf("File descriptors => %d\n", fds);
    if (FD_ISSET(this->listener, &this->readfs))
      {
	create_client(this);
	FD_CLR(this->listener, &this->readfs);
      }
    if (FD_ISSET(0, &this->readfs))
      {
	this->terminate(this);
	close(4);
	return (EXIT_SUCCESS);
      }
    this->clients->for_each(this->clients, on_client_message, this);
  }
}

/**
 * hroux : Rajout d'une réception après un send pour recevoir le
 * "OK message receiv"
 * iricanf: Correction du broadcast, la fonction permet d'envoyer
 * un message dans tous les salons du serveur
 */
void		broadcast_msg(t_server *this, char *msg) {
  t_list_item	*room_node;
  t_list_item	*client_node;
  t_room	*room;
  t_client	*client;

  room_node = this->rooms->head;
  my_str_replace(msg, ' ', '|');
  while (room_node != NULL)
    {
      room = (t_room *) room_node->data;
      client_node = room->clients->head;
      while (client_node != NULL)
	{
	  client = (t_client *) client_node->data;
	  send(client->socket, msg, my_strlen(msg), 0);
	  get_callback_msg(client->socket);
	  client_node = client_node->next;
	}

      room_node = room_node->next;
    }
}


/**
 * hroux : Rajout d'une réception après le send pour recevoir le "OK message receiv"
 */
void		message_priver(t_server *this, char *message,
			       t_client *sender) {
  char		**message_decomposer;
  char		*message_final;
  char		*full_msg;
  t_client	*client;
  t_list_item	*tmp;
  char		err_msg[MSG_LENGTH];

  client = NULL;
  if (test_message_private(&message_decomposer,
			   &message_final, err_msg, sender, message) == 1)
    return;
  tmp = this->clients->head;
  loop_message_priver(tmp, &message_decomposer, &client);
  if (client != NULL)
    envoie_message_priver(&full_msg, sender, message_final, client);
  else
    {
      send(sender->socket, "This|user|is|not|connect\n", 48, 0);
      get_callback_msg(sender->socket);
    }
}

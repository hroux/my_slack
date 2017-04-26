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
    {
      free(server);
      return NULL;
    }
  server->listener = socket(AF_INET, SOCK_STREAM, server->protocol->p_proto);
  if (server->listener == -1)
    {
      free(server);
      return NULL;
    }
  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = INADDR_ANY;
  server->addr.sin_port = htons(PORT);
  if (bind(server->listener, (const struct sockaddr *) &server->addr,
	   sizeof(server->addr)) == -1)
    {
      free(server);
      return (NULL);
    }
  if (listen(server->listener, BACKLOG) == -1)
    {
      free(server);
      return (NULL);
    }
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

int		bind_client(void *server, void *node) {
  t_client	*c;
  t_server	*s;

  c = (t_client *) ((t_list_item *) node)->data;
  s = (t_server *) server;
  FD_SET(c->socket, &s->readfs);
  return (1);
}

void		create_client(t_server *this) {
  t_room	*general;
  t_client	*new_client;
  char		connect_msg[64];
  char		buffer[32];
  int		n;

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
  free(new_client);
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
    buffer[n] = '\0';
    my_printf("Message => %s\n", buffer);
    send_callback_msg(c->socket);
    handle_message(s, buffer, c);
    FD_CLR(c->socket, &s->readfs);
  }
  return (1);
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

int test_message_private(char ***message_decomposer, char** message_final,
			 char *err_msg, t_client *sender, char *message)
{
  *message_decomposer =  my_str_to_wordtab(message);
  *message_final = decode_msg(*message_decomposer);
  if ((message == NULL || my_strlen(message) < 1) ||
      (*message_final == NULL || my_strlen(*message_final) < 1))
    {
      sprintf(err_msg, "name or/and message cannot be empty !\n");
      send(sender->socket, err_msg, my_strlen(err_msg), 0);
      get_callback_msg(sender->socket);
      return 1;
    }
  else
    return 0;
}

void envoie_message_priver(char **full_msg, t_client *sender,
			   char *message_final, t_client *client)
{
  *full_msg = malloc(sizeof(char) * (my_strlen(sender->name) +
				     my_strlen(message_final) + 1024));
  sprintf(*full_msg, "%s : %s\n", sender->name, message_final);
  my_str_replace(*full_msg, ' ', '|');
  send(client->socket, *full_msg, my_strlen(*full_msg), 0);
  get_callback_msg(client->socket);
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
  t_client	*test;
  char		err_msg[MSG_LENGTH];

  client = NULL;
  if (test_message_private(&message_decomposer,
			   &message_final, err_msg, sender, message) == 1)
    return;
  tmp = this->clients->head;
  while (tmp != NULL)
    {
      test = (t_client *) tmp->data;
      if (strcmp(test->name, message_decomposer[0]) == 0)
	client = test;
      tmp = tmp->next;
    }
  if (client != NULL)
    envoie_message_priver(&full_msg, sender, message_final, client);
  else
    {
      send(sender->socket, "This|user|is|not|connect\n", 48, 0);
      get_callback_msg(sender->socket);
    }
}

/**
 *fonction permettant de recevoir le "OK Message receved du client"
 *à mettre après chaque send
 *TODO : logger les message en debbug
 */
void	get_callback_msg(int sock) {
  char	*rep_client;
  int	n;

  if ((rep_client = malloc(sizeof(char) * 1024)) != NULL)
    {
      n = recv(sock, rep_client, 1023, 0);
      if (n > 0)
	{
	  rep_client[n] = '\0';
	  my_printf("%s\n", rep_client);
	}
      free(rep_client);
    }
}

/**
 *fonction permettant de send le "OK Message receved au client"
 *à mettre après chaque send
 *TODO : test si no error + logger
 */
void	send_callback_msg(int sock) {
  char	*rep_client;

  if ((rep_client = my_strdup("OK|Message|received")) != NULL)
    {
      send(sock, rep_client, my_strlen(rep_client), 0);
      free(rep_client);
    }
}

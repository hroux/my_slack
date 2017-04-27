/*
** room.c for my_slack in /home/camille/slack/my_slack/server
**
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
**
** Started on  Wed Apr 26 15:09:14 2017 VRIGNAUD camille
** Last update Wed Apr 26 21:11:20 2017 VRIGNAUD camille
*/

#include <memory.h>
#include <string.h>
#include "includes/server.h"

void	add_client(t_room *this, t_client *client) {
  char	*connect_msg;

  connect_msg = malloc(MSG_LENGTH * sizeof(char));
  if (connect_msg == NULL)
    return;
  client->room = this;
  this->clients->push(this->clients, client);
  my_printf("User %s joined the room => %s\n",
	    client->name, this->name);
  sprintf(connect_msg, "User %s joined the room\n", client->name);
  msg_salon(connect_msg, client, this);
  free(connect_msg);
}

void		remove_client(t_room *this, t_client *client) {
  char		*connect_msg;
  t_list_item	*client_node;

  connect_msg = malloc(sizeof(char) * 1024);
  client_node = get_client_node(this->clients, client);
  if (client_node == NULL)
    my_printf("Cannot find client !!!\n");
  else
    my_printf("Found client => ", ((t_client *) client_node->data)->name);
  if (connect_msg == NULL)
    return;
  my_printf("%s a just quit salon => %s\n", client->name, this->name);
  sprintf(connect_msg, "User %s disconnected to %s\n",
	  client->name, this->name);
  this->send(connect_msg, NULL, this);
  this->clients->remove(this->clients, client_node, FALSE);
  free(connect_msg);
}

void loop_salon(t_list_item	*tmp, char *full_msg, t_client *sender)
{
  t_client	*client;
  while (tmp != NULL)
    {
      client = (t_client *) tmp->data;
      if (sender != NULL && my_strcmp(client->name, sender->name) != 0)
	{
	  send(client->socket, full_msg, my_strlen(full_msg), 0);
	  get_callback_msg(client->socket);
	}
      else
	{
	  send(client->socket, full_msg, my_strlen(full_msg), 0);
	  get_callback_msg(client->socket);
	}
      tmp = tmp->next;
    }
}

void		msg_salon(char *msg, t_client *sender, t_room *room) {
  t_list_item	*tmp;
  char		*full_msg;

  tmp = room->clients->head;
  if (tmp == NULL)
    return;
  if (sender != NULL)
    {
      full_msg = malloc(sizeof(char *) * (my_strlen(sender->name) +
					  my_strlen(msg)));
      sprintf(full_msg, "%s : %s", sender->name, msg);
    }
  else
    full_msg = msg;
  my_str_replace(full_msg, ' ', '|');
  loop_salon(tmp, full_msg, sender);
  if (sender != NULL)
    free(full_msg);
}

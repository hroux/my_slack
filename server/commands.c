/*
** commands.c for my_slack in /home/camille/slack/my_slack/server
**
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
**
** Started on  Wed Apr 26 14:54:09 2017 VRIGNAUD camille
** Last update Wed Apr 26 21:09:28 2017 VRIGNAUD camille
*/

#include "includes/server.h"
#include <string.h>

void		show_rooms_cmd(t_server *server, char *something,
			       t_client *client) {
  t_list_item	*room_node;
  t_room	*r;
  char		msg[MSG_LENGTH];

  room_node = server->rooms->head;
  send(client->socket, "Liste|des|salons|:\n",
       my_strlen("Liste|des|salons|:\n"), 0);
  get_callback_msg(client->socket);
  while (room_node != NULL)
    {
      r = (t_room *) room_node->data;
      sprintf(msg, "#%s\n", r->name);
      my_str_replace(msg, ' ', '|');
      send(client->socket, msg, strlen(msg), 0);
      get_callback_msg(client->socket);
      room_node = room_node->next;
    }
  if (something != NULL) {
    my_printf("Why do you pass this => %s ??", something);
  }
}

void		join_room_cmd(t_server *server,
			      char *room_name, t_client *client) {
  t_room	*next;
  char		err_msg[MSG_LENGTH];
  if (room_name == NULL || my_strlen(room_name) < 1) {
    sprintf(err_msg, "Le nom du salon ne doit pas etre vide !\n");
    my_str_replace(err_msg, ' ', '|');
    send(client->socket, err_msg, my_strlen(err_msg), 0);
    get_callback_msg(client->socket);
    return;
  }

  next = get_room_by_name(server->rooms, room_name);
  if (next == NULL) {
    sprintf(err_msg, "Le salon %s n'existe pas !\n", room_name);
    my_str_replace(err_msg, ' ', '|');
    send(client->socket, err_msg, my_strlen(err_msg), 0);
    get_callback_msg(client->socket);
    return;
  }
  my_printf("next name : %s\n", next->name);
  my_printf("client->room->name : %s\n", client->room->name);
  if (strcmp(next->name, client->room->name) == 0)
    return;
  client->room->remove_client(client->room, client);
  next->add_client(next, client);
	my_printf("client->room->name : %s\n", client->room->name);
}

void		create_room_cmd(t_server *server,
				char *room_name, t_client *client) {
  t_room	*new;
  char		err_msg[MSG_LENGTH];

  if (room_name == NULL || my_strlen(room_name) < 1) {
    sprintf(err_msg, "Room name cannot be empty !\n");
    send(client->socket, err_msg, my_strlen(err_msg), 0);
    get_callback_msg(client->socket);
    return;
  }
  new = create_room(room_name, 0);
  server->rooms->push(server->rooms, new);
  join_room_cmd(server, room_name, client);
}

void    envoie_err(char *err_msg, t_client *client)
{
	my_str_replace(err_msg, ' ', '|');
	send(client->socket, err_msg, my_strlen(err_msg), 0);
	get_callback_msg(client->socket);
}

void		delete_room_cmd(t_server *server, char *room_name,
				t_client *client) {
  t_room	*to_delete;
  t_list_item	*client_node;
  t_client	*c;
  char		err_msg[MSG_LENGTH];


  if (room_name == NULL || my_strlen(room_name) < 1) {
    sprintf(err_msg, "Room name cannot be empty !\n");
    send(client->socket, err_msg, my_strlen(err_msg), 0);
    get_callback_msg(client->socket);
    return;
  }
  to_delete = get_room_by_name(server->rooms, room_name);
  if (to_delete == NULL) {
    sprintf(err_msg, "Le salon %s n'existe pas !\n", room_name);
    envoie_err(err_msg,client);
    return;
  }
  if (to_delete->permanent) {
    sprintf(err_msg, "Le salon %s ne peut pas etre supprimé !\n", room_name);
    envoie_err(err_msg,client);
    return;
  }
  client_node = to_delete->clients->head;
  while (client_node != NULL) {
    c = (t_client *) client_node->data;
    join_room_cmd(server, "general", c);
    client_node = client_node->next;
  }
  server->rooms->remove(server->rooms, get_room_node(server->rooms, to_delete), 0);
}

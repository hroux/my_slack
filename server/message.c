/*
** message.c for my_slack in /home/camille/slack/my_slack/server
**
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
**
** Started on  Wed Apr 26 15:07:03 2017 VRIGNAUD camille
** Last update Wed Apr 26 21:10:44 2017 VRIGNAUD camille
*/

#include <stdlib.h>
#include <memory.h>
#include "includes/server.h"

t_chat_cmd g_chat_cmd[] = {
  {"list", show_rooms_cmd},
  {"join", join_room_cmd},
  {"create", create_room_cmd},
  {"delete", delete_room_cmd},
  {"private", message_priver},
  {NULL, NULL}
};


void		handle_message(t_server *server, char *msg, t_client *sender) {

  int		i;
  t_chat_cmd	chat_cmd;
  char		**splitted_msg;
  char		*message;

  splitted_msg = my_str_to_wordtab(msg);
  for (i = 0; g_chat_cmd[i].cmd != NULL; i++) {
    chat_cmd = g_chat_cmd[i];
    if (strcmp(splitted_msg[0], chat_cmd.cmd) == 0)
      {
	if ((strcmp(splitted_msg[0], "private") == 0) &&
	    (splitted_msg[1] != NULL))
	  {
	    message = decode_msg(splitted_msg);
	    chat_cmd.handler(server, message, sender);
	  }
	else if (splitted_msg[1] != NULL)
	  chat_cmd.handler(server, splitted_msg[1], sender);
	else
	  chat_cmd.handler(server, NULL, sender);

	return;
      }
  }
  sender->room->send(msg, sender, sender->room);
}


char	*decode_msg(char **message_decomposer) {
  int	i = 1;
  int	j = 0;
  char	*message;

  if (message_decomposer == NULL || message_decomposer[0] == NULL ||
      message_decomposer[i] == NULL)
    return (NULL);
  while (message_decomposer[j] != NULL)
    j = j + 1;
  message = malloc(sizeof(message_decomposer[i]) * 1024);
  if (message == NULL)
    return (NULL);
  strcpy(message, message_decomposer[i]);
  i = i + 1;
  while (message_decomposer[i] != NULL) {
    strcat(message, " ");
    strcat(message, message_decomposer[i]);
    strcat(message, " ");
    i = i + 1;
  }
  return (message);
}

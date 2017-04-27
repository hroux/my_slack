#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

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

void loop_message_priver(t_list_item *tmp, char ***message_decomposer,
   t_client **client)
{
    t_client	*test;
  while (tmp != NULL)
  {
  test = (t_client *) tmp->data;
  if (strcmp(test->name, *message_decomposer[0]) == 0)
  *client = test;
  tmp = tmp->next;
  }
}

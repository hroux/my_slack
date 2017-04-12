#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

int VerifMessage(char *buffer)
{
  char **MessageDecomposer;
  char **Commande;
  int		i;
  int		valide;

  valide = 0;
  i = 0;
  Commande = (char **) fill_commande();
  MessageDecomposer = my_str_to_wordtab(buffer);
  if (MessageDecomposer[0] == NULL)
    return 0;
  while (Commande[i] != NULL)
    {
      if (strcmp(Commande[i], MessageDecomposer[0]) == 0)
	       valide = 1;
      i = i + 1;
    }
  i = 0;
  while (MessageDecomposer[i] != NULL)
    i = i + 1;
  if (i > 2 && valide == 1)
    return 1;
  else
    return 0;
}

char **fill_commande()
{
	char **Commande;
	
	Commande = malloc(sizeof(char *) * 2);
  if (Commande == NULL)
    return NULL;
	Commande[0] = strdup("private");
	Commande[1] = strdup("salon");
  Commande[2] = NULL;
	return Commande;	
}

int  type_commande(char *buffer)
{
 char **MessageDecomposer;
 int  i;
 i = 0;
  if (VerifMessage(buffer))
  {
   MessageDecomposer = my_str_to_wordtab(buffer);
    while (MessageDecomposer[i] != NULL)
    {
      if (strcmp("private", MessageDecomposer[i]) == 0)
        return 1;
      if (strcmp("salon", MessageDecomposer[i]) == 0)
        return 2;
      i = i + 1;
    }
  }
    return (0);
}

t_message *Create_message(char *buffer, t_client *client)
{
  t_message *message;
  char	  **message_decomposer;

  message_decomposer = my_str_to_wordtab(buffer);
  message = malloc(sizeof(message));
  buffer = decode_msg(buffer);
  message->msg = malloc(sizeof(buffer));
  message->msg = buffer;
  message->commande = malloc(sizeof(message_decomposer[0]));
  message->commande = message_decomposer[0];
  message->cible = malloc(sizeof(message_decomposer[1]));
  message->cible = message_decomposer[1];
  message->auteur = malloc(sizeof(client));
  message->auteur = client;

  my_printf("Message->msg = %s\n Message->commande = %s\n Message->cible = %s\n Message->auteur = %s\n",
	    message->msg, message->commande, message->cible, message->auteur);
  return message;
}

char    *decode_msg(char *buffer)
{
  int i = 2;
  int j = 0;
  char *message;
  char **message_decomposer;

  message_decomposer = my_str_to_wordtab(buffer);
  while (message_decomposer[j] != NULL)
    j = j + 1 ;
  message = malloc(sizeof(message_decomposer[i])* j);
  if (message == NULL)
    return NULL;
  strcpy(message, message_decomposer[i]);
  i = i + 1;
  while (message_decomposer[i] != NULL)
    {        
      strcat(message, " ");
      strcat(message, message_decomposer[i]);
      strcat(message, " ");
      my_printf("%s\n", message);
      i = i + 1;
    }
  return message;
}

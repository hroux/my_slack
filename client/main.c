/*
** main.c for  in /home/hugues/Documents/C/my_slack/client
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Sun Apr  9 16:00:52 2017 ROUX Hugues
** Last update Sun Apr  9 22:44:53 2017 ROUX Hugues
*/
#include "includes/client.h"

t_client	*client;

/**
 * Met à jour l'ip de connexion et affiche un message
 */
void		set_ip(void *values_list)
{
  t_list	*values;
  char		*ip;

  values = (t_list *) values_list;
  ip = *(char **) values->get(values, 0)->data;
  client->ip = my_strdup(ip);
  my_printf("Setting ip server to => %s\n", ip);
}

/**
 * Met à jour le port de connexion et affiche un message
 */
void		set_port(void *values_list)
{
  t_list	*values;
  char		*port;

  values = (t_list *) values_list;
  port = *(char **) values->get(values, 0)->data;
  client->port = my_strdup(port);
  my_printf("Setting port server to => %s\n", port);
}

/*
 *Définitions des arguments attendus
 */
t_option_field g_options_fields[] = {
  {"ip", "i", "Set the ip server", "0.0.0.0", 1, 0, 0, set_ip},
  {"port", "p", "Set the port server", "8080", 1, 0, 0, set_port},
  {NULL, NULL, NULL, NULL, 0, 0, 0, NULL}
};

int		main(int argc, char **argv){
  t_parser	*parser;

  client = create_client();
  my_printf("Hello, this is slack client!\n");
  parser = create_parser(argc, argv);
  if (parser == NULL)
    {
      my_printf("Error allocation\n");
      return 1;
    }
  if(!parser->validate(parser, g_options_fields))
    return 1;
  client->start(client);
  my_printf("IP : %s\n", client->ip);
  my_printf("PORT : %s\n", client->port);
  parser->free(parser);
  client->free(client);
  return 0;
}

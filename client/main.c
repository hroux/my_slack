/*
** main.c for  in /home/hugues/Documents/C/my_slack/client
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Sun Apr  9 16:00:52 2017 ROUX Hugues
** Last update Mon Apr 17 17:04:05 2017 ROUX Hugues
*/
#include "includes/client.h"

t_client	*client;
t_logger	*Logger;

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
  Logger->info(Logger,"Setting ip server to => %s\n", ip);
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
  Logger->info(Logger,"Setting port server to => %s\n", port);
}

/*
 *Définitions des arguments attendus
 */
t_option_field g_options_fields[] = {
  {"ip", "i", "Set the ip server", "0.0.0.0", 1, 0, 0, set_ip},
  {"port", "p", "Set the port server", "8080", 1, 0, 0, set_port},
  {NULL, NULL, NULL, NULL, 0, 0, 0, NULL}
};

int		main(int argc, char **argv)
{
  t_parser	*parser;
  t_log_cfg	*config;

  if ((config = malloc(sizeof(t_log_cfg))) == NULL)
    return 1;
  config->level = LEVEL_INFO;
  config->logfile = "./journalClient.log";
  Logger = create_logger(config);
  client = create_client();
  my_printf("Hello, this is slack client!\n");
  if ((parser = create_parser(argc, argv)) == NULL)
    {
      Logger->error(Logger,"Error allocation\n");
      return 1;
    }
  if(!parser->validate(parser, g_options_fields))
    {
      Logger->error(Logger,"Error arguments\n");
      return 1;
    }
  client->start(client);
  parser->free(parser);
  client->free(client);
  Logger->free(Logger);
  return 0;
}

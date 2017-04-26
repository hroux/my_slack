/*
** main.c for my_slack in /home/camille/slack/my_slack/server
**
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
**
** Started on  Wed Apr 26 15:05:12 2017 VRIGNAUD camille
** Last update Wed Apr 26 15:06:27 2017 VRIGNAUD camille
*/

#include "includes/server.h"
#include <string.h>

int		main() {
t_server	*server = create_server();

if (server == NULL)
  my_printf("Failed to start server\n");
 else
   server->start(server);
return (0);
}

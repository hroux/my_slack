/*
** logconfig.c for  in /root/libmy_extended/liblog
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:38:37 2017 IRICANIN Filip
** Last update Thu Feb 23 06:38:40 2017 IRICANIN Filip
*/
#include <stdlib.h>
#include "headers/liblog.h"

t_log_cfg	*get_default_cfg()
{
  t_log_cfg *cfg;

  cfg = malloc(sizeof(t_log_cfg));

  if (cfg == NULL)
    {
      return (NULL);
    }
  cfg->level = "debug";
  cfg->logfile = "./journal.log";

  return (cfg);
}

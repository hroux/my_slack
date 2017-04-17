/*
** logger.c for  in /root/libmy_extended/liblog
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:38:51 2017 IRICANIN Filip
** Last update Mon Apr 17 16:23:49 2017 ROUX Hugues
*/
#include <stdlib.h>
#include "../libmy_extended.h"
#include "headers/liblog.h"

t_logger	*create_logger(t_log_cfg *config)
{
  t_logger	*logger;

  logger = malloc(sizeof(t_logger));
  if (logger == NULL)
    return (NULL);
  if (config == NULL)
    config = get_default_cfg();
  init_logger(logger, config);
  return (logger);
}

void		init_logger(t_logger *logger, t_log_cfg *config)
{
  logger->level = get_loglevel(config->level);
  logger->logfile = fopen(config->logfile, "a+");
  logger->free = free_logger;
  logger->debug = debug;
  logger->info = info;
  logger->warn = warning;
  logger->error = error;
  free(config);
}

void		free_logger(t_logger *logger)
{
  fclose(logger->logfile);
  free(logger->level);
  free(logger);
}

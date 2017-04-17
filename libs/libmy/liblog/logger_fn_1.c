/*
** logger_fn_1.c for  in /root/libmy_extended/liblog
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:39:11 2017 IRICANIN Filip
** Last update Mon Apr 17 16:27:11 2017 ROUX Hugues
*/
#include <stdarg.h>
#include <stdlib.h>
#include "../libmy_extended.h"
#include "headers/liblog.h"

#define RESET_COLOR "\033[0m"

int	can_log(t_logger *logger, int weight)
{
  if (weight > logger->level->weight)
    return (0);
  else
    return (1);
}

void		debug(t_logger *logger, char *msg, ...)
{
  va_list	args;
  va_list	copy;

  if (!can_log(logger, 4))
    return;
  va_start(args, msg);
  va_copy(copy, args);
  my_printf("\033[36m[DEBUG] ");
  my_vprintf(msg, args);
  my_printf(RESET_COLOR);
  fprintf(logger->logfile, "[DEBUG] ");
  vfprintf(logger->logfile, msg, copy);
  va_end(copy);
  va_end(args);
}

void	info(t_logger *logger, char *msg, ...)
{
  va_list args;
  va_list copy;

  if (!can_log(logger, 3))
    return;
  va_start(args, msg);
  va_copy(copy, args);
  my_printf("\033[32m[INFO] ");
  my_vprintf(msg, args);
  my_printf(RESET_COLOR);
  fprintf(logger->logfile,"[INFO] ");
  vfprintf(logger->logfile, msg, copy);
  va_end(copy);
  va_end(args);
}

void	warning(t_logger *logger, char *msg, ...)
{
  va_list args;
  va_list copy;
  
  if (!can_log(logger, 2))
    return;
  va_start(args, msg);
  va_copy(copy, args);
  my_printf("\033[33m[WARNING] ");
  my_vprintf(msg, args);
  my_printf(RESET_COLOR);
  fprintf(logger->logfile, "[WARNING] ");
  vfprintf(logger->logfile, msg, copy);
  va_end(copy);
  va_end(args);
}

void	error(t_logger *logger, char *msg, ...)
{
  va_list args;
  va_list copy;
  
  if (!can_log(logger, 1))
    return;
  va_start(args, msg);
  va_copy(copy, args);
  my_printf("\033[31m[ERROR] ");
  my_vprintf(msg, args);
  my_printf(RESET_COLOR);
  fprintf(logger->logfile, "[ERROR] ");
  vfprintf(logger->logfile, msg, copy);
  va_end(copy);
  va_end(args);
}

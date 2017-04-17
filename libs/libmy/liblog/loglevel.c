/*
** loglevel.c for  in /root/libmy_extended/liblog
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:39:30 2017 IRICANIN Filip
** Last update Mon Apr 17 16:24:44 2017 ROUX Hugues
*/
#include <stdlib.h>
#include <string.h>
#include "../libmy_extended.h"
#include "headers/liblog.h"

t_loglevel	*get_loglevel(char *level)
{
  int		i;
  t_loglevel	*ret;
  t_loglevel	levels[] = {
    {"debug", 4},
    {"info", 3},
    {"warning", 2},
    {"error", 1},
    {NULL, 0}
  };

  ret = malloc(sizeof(t_loglevel));
  for (i = 0; levels[i].name != NULL; i++) {
    if (strcmp(level, levels[i].name) == 0 || level == NULL) {
      ret->name = levels[i].name;
      ret->weight = levels[i].weight;
    }
  }
  if (ret->name == NULL) {
    ret->name = levels[0].name;
    ret->weight = levels[0].weight;
  }
  return (ret);
}

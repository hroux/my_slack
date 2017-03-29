/*
** option_functions_1.c for libmy_extended in /Users/Regency/libmy_extended/libparse
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:28:49 2017 IRICANIN Filip
** Last update Thu Feb 23 06:35:34 2017 IRICANIN Filip
*/
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "headers/parser.h"

void		get_opt_values(t_parser *this, t_option *opt, int start)
{
  int i;
  char *arg;

  for (i = start; i < this->argc; i++) {
    arg = this->argv[i];
    if (is_option(arg))
      {
	return;
      }
    opt->values->push(opt->values, &arg);
  }
}

t_option		*find_option_by_name(t_list *options, char *name)
{

  t_list_item *tmp;
  t_option *opt;

  tmp = options->head;
  while (tmp != NULL)
    {
      opt = (t_option *) tmp->data;

      if (strcmp(opt->name, name) == 0)
	{
	  return opt;
	}
      tmp = tmp->next;
    }

  return NULL;
}

int		is_option(char *arg) {
  if (arg[0] == '-')
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

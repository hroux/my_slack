/*
** arg_functions_1.c for libmy_extended in /Users/Regency/libmy_extended/libparse
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:22:31 2017 IRICANIN Filip
** Last update Fri Feb  3 09:24:31 2017 IRICANIN Filip
*/
#include <stdlib.h>
#include "headers/parser.h"

int		is_option_value(t_parser *this, int index)
{
  int	i;
  char *arg;

  if (index < 1)
    {
      return 1;
    }

  for (i = (index - 1); i > 0; i--)
    {
      arg = this->argv[i];
      if (is_option(arg))
	return 1;
    }

  return 0;
}

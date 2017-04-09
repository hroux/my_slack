/*
** parser.c for libmy_extended in /Users/Regency/libmy_extended/libparse
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:32:01 2017 IRICANIN Filip
** Last update Sun Apr  9 16:43:24 2017 ROUX Hugues
*/
#include <stdio.h>
#include <stdlib.h>
#include "headers/parser.h"
#include "../liblist/headers/list.h"

t_parser		*create_parser(int argc, char **argv)
{
  t_parser *parser;

  parser = malloc(sizeof(t_parser));
  if (parser == NULL)
    {
      return NULL;
    }
  parser->argc = argc;
  parser->argv = argv;
  parser->args = create_list(sizeof(char *), free_arg);
  parser->options = create_list(sizeof(t_option), NULL);
  parser->validate = validate;
  parser->free = free_parser;
  parse_args(parser);
  parse_options(parser);
  return parser;
}

void		parse_args(t_parser *this)
{
  int i;
  char *arg;

  for (i = 1; i < this->argc; i++) {
    arg = this->argv[i];
    if (!is_option(arg))
      {
	if (!is_option_value(this, i))
	  {
	    this->args->push(this->args, &arg);
	  }
      }
  }
}

void		parse_options(t_parser *this)
{

  int i;
  char *arg;
  t_option *opt;

  for (i = 1; i < this->argc; i++)
    {
      arg = this->argv[i];
      if (is_option(arg))
	{
	  opt = malloc(sizeof(t_option));
	  opt->name = remove_all_chars(arg, '-');
	  opt->values = create_list(sizeof(char *), free_arg);
	  get_opt_values(this, opt, i+1);
	  this->options->push(this->options, opt);
	  free(opt);
	}
    }
}

void		free_arg(void *arg)
{
  if (arg != NULL)
    {
      //free(*(char **)arg);
    }
}

void		free_opt(void *opt)
{
  free((t_option *)opt);
}

/*
** main.c for libmy_extended in /Users/Regency/libmy_extended/libparse
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:28:10 2017 IRICANIN Filip
** Last update Thu Feb 23 06:23:09 2017 IRICANIN Filip
*/
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "headers/parser.h"
#include "../liblist/headers/list.h"

void		set_port(void *values_list)
{

  t_list *values;
  char *port;

  values = (t_list *) values_list;
  port = *(char **) values->get(values, 0)->data;

  printf("Setting server port to => %s\n", port);
}

t_option_field g_options_fields[] = {
  // Name, Shortcut, Description, Default Value, Required, Multiple Values
  {"port", "p", "Set the server port", "8080", 1, 0, 0, set_port},
  {NULL, NULL, NULL, NULL, 0, 0, 0, NULL}
};

//int		for_each_opt_value(void *arg, void *value)
//{
//  printf("Option Value => %s\n", *(char **)value);
//  return 1;
//}

int		for_each_arg(void *arg, void *value)
{
  t_list_item *item;

  item = (t_list_item *)value;

  if (!arg)
    printf(" ");
  
  printf("Argument => %s\n", *(char **)item->data);
  return 1;
}

//int		for_each_opt(void *arg, void *opt)
//{
//  t_option *option;
//
//  option = (t_option *) opt;
//  printf("Option => %s\n", option->name);
//  if (option->values != NULL)
//    {
//      option->values->for_each(option->values, for_each_opt_value, NULL);
//    }
//  return 1;
//}


int		main(int argc, char **argv)
{

  t_parser *parser;

  parser = create_parser(argc, argv);

  printf("Args size => %d\n", parser->args->size);
  
  // parser->args->for_each(parser->args, for_each_arg, NULL);
  //    parser->options->for_each(parser->options, for_each_opt);

  //  if(!parser->validate(parser, g_options_fields))
  // {
  //   return 1;
  // } 
  parser->free(parser);
 
  return 0;
}

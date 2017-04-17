/*
** parser_functions_1.c for libmy_extended in /Users/Regency/libmy_extended/libparse
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:35:34 2017 IRICANIN Filip
** Last update Mon Apr 17 16:41:48 2017 ROUX Hugues
*/
#include <stdlib.h>
#include "headers/parser.h"

t_option	*get_option_by_field(t_list *options,
				     t_option_field field)
{
  t_option	*option;

  option = find_option_by_name(options, field.name);
  if (option == NULL && field.shortcut != NULL)
    option = find_option_by_name(options, field.shortcut);
  return (option);
}

void		exec_field_callback(t_option_callback callback, void *param)
{
  if (callback == NULL)
    return;
  if (param != NULL)
    callback(param);
  else
    callback(NULL);
}

t_list		*default_value_to_list(char *default_value)
{
  t_list	*list;
  
  list = create_list(sizeof(char *), NULL);
  list->push(list, &default_value);
  return (list);
}

int			validate(t_parser *this, t_option_field fields[])
{
  int			i;
  t_option		*option;
  t_option_field	field;
  t_list		*default_values;

  for (i = 0; fields[i].name != NULL; i++)
    {
      field = fields[i];
      option = get_option_by_field(this->options, field);
      if (option == NULL)
	{
	  if (field.required)
	    return (0);
	  else
	    {
	      default_values =  default_value_to_list(field.default_value);
	      exec_field_callback(field.callback, default_values);
	      default_values->free(default_values);
	    }
	}
      if (option != NULL)
	{
	  if (option->values->size == 0 && field.has_value)
	    return (0);          
	  else
	    exec_field_callback(field.callback, option->values);
	}
    }
  return 1;
}

void		free_parser(t_parser *this)
{
  this->args->free(this->args);
  this->options->for_each(this->options, free_opt_values, NULL);
  this->options->free(this->options);
  free(this);
  this = NULL;
}


int		free_opt_values(void *arg, void *value) {
  t_list_item *item;
  t_option *opt;

  if (arg == NULL)
    {
      arg = NULL;
    }
  item = (t_list_item *)value;
  opt = (t_option *)item->data;

  opt->values->free(opt->values);

  return (1);
}

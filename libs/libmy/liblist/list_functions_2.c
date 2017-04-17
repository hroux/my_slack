/*
** list_functions_2.c for libmy_extended in /Users/Regency/libmy_extended/liblist
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:15:58 2017 IRICANIN Filip
** Last update Mon Apr 17 16:34:47 2017 ROUX Hugues
*/
#include <stdlib.h>
#include "headers/list.h"

void		list_free(t_list *this)
{
  this->clear(this);
  free(this);
  this = NULL;
}

void		list_for_each(t_list *this, t_iterator iterator, void *arg)
{
  t_list_item	*tmp;
  t_list_item	*next;
  int		result;

  tmp = this->head;
  result = 1;
  if (iterator == NULL)
    return;
  while (tmp != NULL && result)
    {
      next = tmp->next;
      if (arg != NULL)
	result = iterator(arg, tmp);
      else
	result = iterator(NULL, tmp);
      tmp = next;
    }
}

void		list_copy(t_list *this, t_list *dest) {

  t_list_item *tmp;

  tmp = this->head;
  while (tmp != NULL) {
    dest->push(dest, tmp->data);
    tmp = tmp->next;
  }
}

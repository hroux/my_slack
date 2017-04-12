/*
** list_functions_1.c for libmy_extended in /Users/Regency/libmy_extended/liblist
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:11:40 2017 IRICANIN Filip
** Last update Thu Feb 23 06:34:24 2017 IRICANIN Filip
*/
#include <stdlib.h>
#include "headers/list.h"
#include <stdio.h>

t_list_item		*get_node_at_index(t_list *this, int index)
{

  t_list_item *tmp;

  tmp = this->head;

  if (index < 0 || index > this->size)
    {
      return NULL;
    }
  while (tmp != NULL) {
    if (index == tmp->index)
      {
	return tmp;
      }
    tmp = tmp->next;
  }
  return NULL;
}

void		remove_node_at_index(t_list *this, int index)
{
  t_list_item *tmp;

  tmp = get_node_at_index(this, index);
  if (tmp == NULL)
    {
      return;
    }
  remove_node(this, tmp);
}

void		remove_node(t_list *this, t_list_item *item)
{
  // Milieu
  printf("%d\n", this->size);
  printf("%d\n", item->index);
  if (item->prev && item->next) {
    printf("if 1");
    item->prev->next = item->next;
    item->next->prev = item->prev;
  } // Debut
  else if (!item->prev && item->next) {
    printf("if 2");
    this->head = item->next;
    this->head->prev = NULL;
  } // Fin
  else if (!item->next && item->prev) {
    printf("if 3");
    this->tail = item->prev;
    this->tail->next = NULL;
  }
  else {
    printf("if 4");
    this->head = NULL;
    this->tail = NULL;
  }
  this->size--;
  printf("if 5");
  if (this->free_data)
    this->free_data(item->data);
  free(item->data);
  free(item);
  reset_indexes(this);
}

void		reset_indexes(t_list *this)
{
  int i;
  t_list_item *tmp;

  i = 0;
  tmp = this->head;
  while (tmp != NULL)
    {
      tmp->index = i;
      i++;
      tmp = tmp->next;
    }
}

int		list_length(t_list *this)
{
  return this->size;
}

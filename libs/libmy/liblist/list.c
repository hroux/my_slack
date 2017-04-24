/*
** list.c for libmy_extended  in /Users/Regency/libmy_extended/liblist
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:06:48 2017 IRICANIN Filip
** Last update Mon Apr 17 16:33:27 2017 ROUX Hugues
*/
#include <stdlib.h>
#include "headers/list.h"
#include <string.h>

t_list		*create_list(size_t item_size, t_free_fn free_data)
{
  t_list	*list;

  list = (t_list *) malloc(sizeof(t_list));
  if (list == NULL)
    return NULL;
  list->data_size = item_size;
  list->free_data = free_data;
  list_init(list);
  return list;
}

void		list_init(t_list *this)
{
  this->head = NULL;
  this->tail = NULL;
  this->size = 0;
  this->push = list_push;
  this->pop = list_pop;
  this->clear = list_clear;
  this->free = list_free;
  this->get = get_node_at_index;
  this->find = get_node_by_data;
  this->remove_at = remove_node_at_index;
  this->remove = remove_node;
  this->length = list_length;
  this->for_each = list_for_each;
  this->copy = list_copy;
}

void		list_push(t_list *this, void *item)
{
  t_list_item	*node;

  node = (t_list_item *) malloc(sizeof(t_list_item));
  if (node == NULL)
    return;
  node->data = malloc(this->data_size);
  node->prev = NULL;
  node->next = NULL;
  node->index = this->size;
  if (node->data == NULL)
    return;
  memcpy(node->data, item, this->data_size);
  if(this->size == 0)
    {
      this->head = node;
      this->tail = node;
    }
  else
    {
      this->tail->next = node;
      node->prev = this->tail;
      this->tail = node;
    }
  this->size++;
}

void		list_pop(t_list *this)
{
  this->remove(this, this->tail, 1);
}

void		list_clear(t_list *this)
{
  t_list_item	*current;

  while (this->head != NULL) {
    current = this->head;
    this->head = current->next;
    if (this->free_data)
      this->free_data(current->data);
    free(current->data);
    free(current);
    this->size--;
  }
}

/*
** list.h for  in /root/libmy_extended/liblist
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:42:47 2017 IRICANIN Filip
** Last update Thu Feb 23 06:42:48 2017 IRICANIN Filip
*/
#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>

typedef void (*t_free_fn)(void *);
typedef int (*t_iterator)(void *, void *);

typedef struct s_list_item {
    struct s_list_item *prev;
    struct s_list_item *next;
    void *data;
    int index;
} t_list_item;

typedef struct s_list {
    t_list_item *head;
    t_list_item *tail;
    int size;
    size_t data_size;
    t_free_fn free_data;

  void(*push)(struct s_list*, void *item);
  void(*pop)(struct s_list*);
  void(*clear)(struct s_list*);
  void(*free)(struct s_list*);
  t_list_item*(*get)(struct s_list*, int index);
  void(*remove)(struct s_list*, t_list_item *);
  void(*remove_at)(struct s_list*, int index);
  int(*length)(struct s_list*);
  void(*for_each)(struct s_list*, t_iterator, void *);
  void(*copy)(struct s_list *, struct s_list *);
  t_list_item*(*find)(struct s_list *, void *);
  
} t_list;

t_list *create_list(size_t, t_free_fn);
void list_init(t_list *);
void list_push(t_list *, void *);
void list_pop(t_list *);
void list_clear(t_list *);
void list_free(t_list *);
t_list_item *get_node_at_index(t_list *, int);
t_list_item *get_node_by_data(t_list *, void *);
void remove_node_at_index(t_list *, int);
void remove_node(t_list *, t_list_item *);
int list_length(t_list *);
void reset_indexes(t_list *);
void list_for_each(t_list *this, t_iterator iterator, void *arg);
void list_copy(t_list *, t_list *);

#endif // __LIST_H__

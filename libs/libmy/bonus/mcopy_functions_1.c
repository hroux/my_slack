/*
** mcopy_functions_1.c for  in /root/libmy_extended/bonus
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:41:20 2017 IRICANIN Filip
** Last update Thu Feb 23 06:41:22 2017 IRICANIN Filip
*/
#include "multicopy.h"

int		await_thread(void *arg, void *value) {
  t_list_item	*list_item;
  t_mcopy	*mcopy;
  t_pool_item	*pool_item;
  //  void		**thread_return;

  mcopy = (t_mcopy *)arg;
  list_item = (t_list_item *)value;
  pool_item = (t_pool_item *)list_item->data;
  pthread_join(*(pool_item->thread), NULL);

  mcopy->pool->remove(mcopy->pool, list_item);
  my_printf("Pool size => %d\n", mcopy->pool->size);
  
  return (1);
}

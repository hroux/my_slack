/*
** mcopy_functions_2.c for  in /root/libmy_extended/bonus
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:41:30 2017 IRICANIN Filip
** Last update Thu Feb 23 06:41:32 2017 IRICANIN Filip
*/
#include <stdlib.h>
#include "multicopy.h"

void		free_pool_item(void *item) {

  t_pool_item *pool_item;

  pool_item = (t_pool_item *)item;

  //  free(pool_item->src);
  free(pool_item->dest);
  free(pool_item->thread);
}

void		free_queue_item(void *item) {
  free(*(char **)item);
}

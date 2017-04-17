/*
** mcopy.c for  in /root/libmy_extended/bonus
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:14:14 2017 IRICANIN Filip
** Last update Thu Feb 23 06:29:55 2017 IRICANIN Filip
*/

#include <stdlib.h>
#include "multicopy.h"

t_mcopy		*create_mcopy(int argc, char **argv) {

  t_mcopy *mcopy;

  mcopy = malloc(sizeof(t_mcopy));
  if (mcopy == NULL)
    return (NULL);

  mcopy->start = start_mcopy;
  mcopy->free = mcopy_free;
  mcopy->dest = NULL;
  mcopy->queue = create_list(sizeof(char *), free_queue_item);
  mcopy->pool = create_list(sizeof(t_pool_item), free_pool_item);
  mcopy->parser = create_parser(argc, argv);
  
  return (mcopy);
}

void		mcopy_free(t_mcopy *this) {
  this->queue->free(this->queue);
  this->pool->free(this->pool);
  if (this->dest != NULL)
    free(this->dest);
  if (this->parser != NULL)
    this->parser->free(this->parser);
  free(this);
}

void		start_mcopy(t_mcopy *mcopy) {

  t_list *args;
  t_option *opt;
  char *dest;
  
  opt = find_option_by_name(mcopy->parser->options, "dest");
  dest = *(char **) opt->values->get(opt->values, 0)->data;
  mcopy->dest = malloc(sizeof(char) * my_strlen(dest) + 1);
  mcopy->dest = my_strcpy(mcopy->dest, dest);
 
  args = mcopy->parser->args;
  args->copy(args, mcopy->queue);
  mcopy->parser->free(mcopy->parser);
  mcopy->parser = NULL;
  
  mcopy->queue->for_each(mcopy->queue, create_thread, mcopy);
  mcopy->pool->for_each(mcopy->pool, await_thread, mcopy);
}

int		create_thread(void *arg, void *value) {

  t_mcopy	*mcopy;
  t_pool_item	*item;
  
  item = malloc(sizeof(t_pool_item));
  mcopy = (t_mcopy *)arg;
 
  if (item == NULL)
    return (0);

  item->src = *(char **)(((t_list_item *)value)->data);
  item->dest = malloc(sizeof(char) * (my_strlen(mcopy->dest) + my_strlen(item->src) + 1));
  item->dest = my_strcat(my_strcpy(item->dest, mcopy->dest), item->src);
  item->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
  item->thread = malloc(sizeof(pthread_t));

  if (item->thread == NULL) {
    Logger->error(Logger, "Unable to create thread, malloc failed\n");
    return (0);
  }
 
  Logger->info(Logger, "Creating thread, source : %s, dest: %s\n", item->src, item->dest);
  mcopy->pool->push(mcopy->pool, item);
  pthread_create(item->thread, NULL, exec_thread, item);

  return (1);
}

void		*exec_thread(void *arg) {

  t_pool_item	*item;

  item = (t_pool_item *)arg;

  if (item == NULL)
    pthread_exit((void *)0);

  pthread_mutex_lock(&item->mutex);
  Logger->info(Logger, "[THREAD] Starting to copy file => %s to %s\n", item->src, item->dest);
  copy_file(item->src, item->dest);
  pthread_mutex_unlock(&item->mutex);
  
  pthread_exit((void *)1);
}

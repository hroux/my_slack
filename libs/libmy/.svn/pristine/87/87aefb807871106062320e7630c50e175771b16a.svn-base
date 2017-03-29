/*
** multicopy.h for  in /root/Projets/libmy_extended/bonus
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Wed Feb 15 09:35:57 2017 IRICANIN Filip
** Last update Thu Feb 23 06:44:21 2017 IRICANIN Filip
*/
#ifndef __MULTICOPY_H__
#define __MULTICOPY_H__

#include <pthread.h>
#include "../libmy_extended.h"
#include "string_utils.h"

typedef struct s_mcopy {
  t_list	*pool;
  t_list	*queue;
  t_parser	*parser;
  char		*dest;
  
  void (*start)(struct s_mcopy *);
  void (*free)(struct s_mcopy *);
  
} t_mcopy;

typedef struct s_pool_item {
  char		*src;
  char		*dest;
  pthread_t	*thread;
  pthread_mutex_t mutex;
} t_pool_item;

// Multicopy
t_mcopy		*create_mcopy(int argc, char **argv);
int		copy_file(char *src, char *dest);
void		start_mcopy(t_mcopy *mcopy);
int		create_thread(void *, void *);
void		*exec_thread(void *);
int             await_thread(void *arg, void *value);
void		free_pool_item(void *);
void		free_queue_item(void *);
void            mcopy_free(t_mcopy *this);

#endif // __MULTICOPY_H__

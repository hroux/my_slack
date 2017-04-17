/*
** main.c for libmy_extended  in /Users/Regency/libmy_extended/liblist
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Fri Feb  3 09:20:09 2017 IRICANIN Filip
** Last update Fri Feb 17 10:40:24 2017 IRICANIN Filip
*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "headers/list.h"

void		free_str(void *data)
{
  free(*(char **)data);
}

int		for_each_str(void *arg, void *data)
{

  t_list_item *item;

  item = (t_list_item *)data;
  if (arg == NULL)
    printf("Argument is null\n");
  else
    printf("Argument value => %d\n", *(int *)arg);
  
  printf("Found string value: %s\n", *(char **)item->data);
  return 1;
}

int main()
{
  t_list *str_list;
  char *item1;
  char *item2;
  char *item3;
  char *item4;
  int	arg;
  
  str_list = create_list(sizeof(char *), free_str);
  item1 = strdup("My First node");
  item2 = strdup("My Second node");
  item3 = strdup("My Third node");
  item4 = strdup("My Fourth node");
  arg = 1337;
  str_list->push(str_list, &item1);
  str_list->push(str_list, &item2);
  str_list->push(str_list, &item3);
  str_list->push(str_list, &item4);
  str_list->for_each(str_list, for_each_str, &arg);
  str_list->free(str_list);
  str_list = NULL;

  return 0;
}


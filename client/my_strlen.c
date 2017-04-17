/*
** my_strlen.c for  in /home/hugues/DEVC/Jour03/roux_a/my_strlen
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Thu Oct 20 10:32:33 2016 ROUX Hugues
** Last update Sun Jan 29 15:43:20 2017 ROUX Hugues
*/

#include	<stdlib.h>

int		my_strlen(char *str)
{
  int		result;

  if (str == NULL)
    return (0);
  result = 0;
  while (*str != '\0')
    {
      str = str + 1;
      result = result + 1;
    }
  return (result);
}

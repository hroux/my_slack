/*
** my_strcpy.c for  in /home/hugues/DEVC/Jour04/roux_a/my_strcpy
**
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
**
** Started on  Fri Oct 21 11:15:47 2016 ROUX Hugues
** Last update Sun Feb 12 21:24:33 2017 ROUX Hugues
*/

#include	<stdlib.h>
#include "includes/server.h"

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  if (s1 == NULL || s2 == NULL)
    return (-2);
  i = 0;
  while (s1[i] != '\0')
    {
      if (s1[i] > s2[i])
	return (1);
      else if (s1[i] < s2[i])
	return (-1);
      i++;
    }
  if (s2[i] != '\0')
    return (-1);
  return (0);
}

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  if (dest == NULL || src == NULL)
    return NULL;
  i = 0;
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = '\0';
  return (dest);
}

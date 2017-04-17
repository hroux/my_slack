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

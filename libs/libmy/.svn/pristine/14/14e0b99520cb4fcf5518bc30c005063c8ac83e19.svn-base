/*
** string_utils.c for  in /root/libmy_extended/bonus
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:41:52 2017 IRICANIN Filip
** Last update Thu Feb 23 06:41:55 2017 IRICANIN Filip
*/
#include <stdlib.h>
#include "string_utils.h"

char		*my_strcat(char *str1, char *str2)
{
  int	i;
  int	len;
  
  i = 0;
  len = my_strlen(str1);
  while (str2[i] != '\0')
    {
      str1[len + i] = str2[i];
      i++;
    }
  str1[len + i] = '\0';
  
  return (str1);
}

int		my_strlen(char *str)
{
  int   i;

  i = 0;
  while (str[i] != '\0')
    {
      i++;
    }
  return (i);
}

int		my_strcmp(char *s1, char *s2)
{
  int   i;

  i = 0;
  while (s1[i] != '\0' || s2[i] != '\0')
    {
      if (s1[i] < s2[i])
	{
	  return (-1);
	}
      if (s1[i] > s2[i])
	{
	  return (1);
	}
      i++;
    }
  return (0);
}

char		*my_strdup(char *str)
{
  char	*dest;

  dest = malloc(sizeof(char) * my_strlen(str));
  my_strcpy(dest, str);
  return (dest);
}

char		*my_strcpy(char *dest, char *src)
{
  int   i;
  int   n;

  i = 0;
  n = my_strlen(src);
  while (i < n && src[i] != '\0')
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = '\0';
  return (dest);
}

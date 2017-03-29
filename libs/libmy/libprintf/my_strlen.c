/*
** my_strlen.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
**
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Fri Mar 6 17:47:14 2014 IRICANIN Filip
*/

#include "functions.h"

int	my_strlen(char *str)
{
  int   i;

  i = 0;
  while (str[i] != '\0')
    {
      i++;
    }
  return (i);
}

/*
** my_strcmp.c for  in /home/hugues/Documents/C/my_slack/client
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Wed Apr 19 10:34:00 2017 ROUX Hugues
** Last update Wed Apr 19 10:34:26 2017 ROUX Hugues
*/

#include <stdlib.h>

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

/*
** my_strncmp.c for  in /home/hugues/DEVC/Jour04/roux_a/my_strncmp
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Fri Oct 21 14:20:50 2016 ROUX Hugues
** Last update Sun Apr  9 21:36:53 2017 ROUX Hugues
*/

void	my_inc(char **s1, char **s2, int *i)
{
  *s1 = *s1 + 1;
  *s2 = *s2 + 1;
  *i = *i + 1;
}

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  i = 1;
  while (*s1 != '\0' && *s2 != '\0' && i <= n)
    {
      if (*s1 < *s2)
	  return (-1);
      if (*s1 > *s2)
	  return (1);
      my_inc(&s1, &s2, &i);
      if (*s1 == '\0' && *s2 != '\0' && i <= n)
	  return (-1);
      if (*s2 == '\0' && *s1 != '\0' && i <= n)
	  return (1);
    }
  return (0);
}

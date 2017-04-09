/*
** readline.c for  in /home/hugues/Documents/C/Battle_for_midgard/roux_a/Introduction
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Tue Dec  6 15:57:02 2016 ROUX Hugues
** Last update Sun Apr  9 22:29:35 2017 ROUX Hugues
*/
#include <unistd.h>
#include <stdlib.h>

int	my_str_is_printable(char str[])
{
  int	i;
  int	boolean;

  i = 0;
  boolean = 1;
  while (str[i] != '\0')
    {
      if (str[i] < 32 || str[i] > 126)
	{
	  boolean = 0;
	}
      i = i + 1;
    }
  return (boolean);
}

char		*readLine()
{
  ssize_t	ret;
  char		*buff;

  if ((buff = malloc(sizeof(*buff) * (50 + 1))) == NULL)
    return (NULL);
  if ((ret = read(0, buff, 50)) > 1)
    {
      buff[ret - 1] = '\0';
      if (my_str_is_printable(buff) == 0)
	{
	  free(buff);
	  return (NULL);
	}
      return (buff);
    }
  buff[0] = '\0';
  if (my_str_is_printable(buff) == 0)
    {
      free(buff);
      return (NULL);
    }
  return (buff);
}

int	my_rand(int val1, int val2)
{
  int	random;

  random = (rand() % val2) + val1;
  return (random);
}

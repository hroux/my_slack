/*
** my_str_to_wordtab.c for c in /home/camille/Jour07C/ex3
** 
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
** 
** Started on  Mon Oct 24 14:48:30 2016 VRIGNAUD camille
** Last update Tue Oct 25 17:19:04 2016 VRIGNAUD camille
*/

#include <stdio.h>
#include <stdlib.h>

int	my_strlen(char *str);

int	is_alpha_numeric(char c)
{
  if (c >= 48 && c <= 57)
    return (1);
  else if (c >= 65 && c <= 90)
    return (1);
  else if (c >= 97 && c <= 122)
    return (1);
  else
    return (0);
}

void	count_char(char *str, char **tab)
{
  int	j;
  int	i;
  int carc;

  carc = 0;
  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      while (is_alpha_numeric(str[i]) == 1)
	{
	  carc = carc + 1;
	  i = i + 1;
	}
      if (carc != 0)
	{
	  carc = carc + 1;
	  tab[j] = malloc((carc) * sizeof(char));
	  j = j + 1;
	  carc = 0;
	}
      i = i + 1;
    }
}


int	count_word(char *str)
{
  int	word;
  int	i;

  i = 0;
  word = 0;
  while (i < my_strlen(str))
    {
      if (is_alpha_numeric(str[i]) == 1 && is_alpha_numeric(str[i + 1]) == 0)
	word = word + 1;
      i = i + 1;
    }
  return (word);
}

void	my_fill_tab(char *str, char **tab)
{
  int	i;
  int	j;
  int	temp;

  i = 0;
  j = 0;
  temp = 0;
  while (str[i] != '\0')
    {
      while (is_alpha_numeric(str[i]) == 1)
	{
	  tab[j][temp] = str[i];
	  temp = temp + 1;
	  i = i + 1;
	}
      if (temp != 0)
	{
	  tab[j][temp + 1] = '\0';
	   temp = 0;
	   j = j + 1;
	}
      i = i + 1;
    }
}

char	**my_str_to_wordtab(char *str)
{
  if (str != NULL)
    {
      int	nbWorld;
      char	**tab;

      nbWorld = 0;
      nbWorld = count_word(str);
      tab = malloc((nbWorld + 1) * sizeof(char*));
      count_char(str, tab);
      my_fill_tab(str, tab);
      tab[nbWorld] = NULL;
      return (tab);
    }
  else
    return (0);
}

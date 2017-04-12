/*
** my_str_to_wordtab.c for  in /home/hugues/DEVC/Jour07/roux_a/my_str_to_wordtab
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Mon Oct 24 12:41:07 2016 ROUX Hugues
** Last update Wed Oct 26 11:03:17 2016 ROUX Hugues
*/

#include <stdlib.h>

char	*my_strchr(char *str);
char	*my_strncpy(char *dest, char *src, int n);

char	*inc_str(char *str)
{
  while ((!((*str > 47 && *str < 58) ||
	    (*str > 64 && *str < 91) ||
	    (*str > 96 && *str < 123))) && *str != '\0')
    {
      str = str + 1;
    }
  return (str);
}

int	str_len_spec(char *str)
{
  int	result;

  result = 0;
  while (((*str > 47 && *str < 58) ||
	  (*str > 64 && *str < 91) ||
	  (*str > 96 && *str < 123)) && *str != '\0')
    {
      result = result + 1;
      str = str + 1;
    }
  return (result);
}

int	nb_words(char *str)
{
  int	result;
  char	*st;

  result = 0;
  st = str;
  while (st != NULL && *st != '\0')
    {
      st = inc_str(st);
      result = result + 1;
      st = my_strchr(st);
      st = inc_str(st);
    }
  return (result);
}

char	*add(char *temp_str, char **result)
{
  int	length;
  char	*string;
  
  temp_str = inc_str(temp_str);
  length = str_len_spec(temp_str);
  string = malloc((length + 1) * sizeof(char));
  if (string == NULL)
    return (NULL);
  string = my_strncpy(string, temp_str, length);
  string[length] = '\0';
  *result = string;
  temp_str = my_strchr(temp_str);
  temp_str = inc_str(temp_str);
  return (temp_str);
}

char	**my_str_to_wordtab(char *str)
{
  int	count_words;
  int	i;
  char	**result;
  char	**result_bis;
  char	*temp_str;

  i = 0;
  count_words = nb_words(str);
  result = malloc((count_words + 1) * 8);
  if (result == NULL)
    return (NULL);
  result_bis = result;
  temp_str = str;
  while (i != count_words)
    {
      temp_str = add(temp_str, result);
      result = result + 1;
      i = i + 1;
    }
  *result = NULL;
  return (result_bis);
}

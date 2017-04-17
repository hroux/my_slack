/*
** my_strstr.c for  in /home/hugues/DEVC/Jour04/roux_a/my_strstr
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Fri Oct 21 20:42:10 2016 ROUX Hugues
** Last update Sun Apr  9 21:36:10 2017 ROUX Hugues
*/

void	my_inc(char **s1, char **s2, int *i);
int	my_strncmp(char *s1, char *s2, int n);
int	my_strlen(char *str);

char	*my_strstr(char *str, char *to_find)
{
  int	result;
  int	len_to_find;

  len_to_find = my_strlen(to_find);
  while (*str != '\0')
    {
      if (*to_find == *str)
	{
	  result = my_strncmp(str, to_find, len_to_find);
	  if (result == 0)
	    return (str);
	}
      str = str + 1;
    }
  return ((void*)0);
}

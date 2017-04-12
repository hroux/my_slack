/*
** my_strchr.c for  in /home/hugues/DEVC/Jour03/roux_a/my_strchr
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Thu Oct 20 10:57:19 2016 ROUX Hugues
** Last update Wed Oct 26 11:05:14 2016 ROUX Hugues
*/

void	my_putchar(char c);
char	*inc_str(char *str);

char	*my_strchr(char *str)
{
  while (*str != '\0')
    {
      if (!((*str > 47 && *str < 58) ||
	   (*str > 64 && *str < 91) ||
	   (*str > 96 && *str < 123)))
	{
	  return (str);
	}
      str = str + 1;
    }
  return (str);
}

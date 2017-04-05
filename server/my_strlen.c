/*
** my_strlen.c for c in //home/camille/Jour03C/ex2
** 
** Made by VRIGNAUD camille
** Login   <vrigna_c@etna-alternance.net>
** 
** Started on  Thu Oct 20 10:40:44 2016 VRIGNAUD camille
** Last update Tue Oct 25 17:02:36 2016 VRIGNAUD camille
*/

int	my_strlen(char *str)
{
  int	 i;

  i = 0;
  while (*str != '\0')
    {
      i = i + 1;
      str = str + 1;
    }
  return (i);
}

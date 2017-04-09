/*
** my_getnbr.c for  in /home/hugues/DEVC/Jour05/my_getnbr
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Sat Oct 22 14:58:05 2016 ROUX Hugues
** Last update Sun Apr  9 21:55:33 2017 ROUX Hugues
*/

char	*is_neg(char *str, int *neg)
{
  int	neg_bis;

  neg_bis = 1;
  while (*str == 45 || *str == 43)
    {
      if (*str == 45)
	neg_bis = neg_bis * -1;
      str = str + 1;
    }
  *neg = neg_bis;
  return (str);
}

int	my_getnbr(char *str)
{
  int	nb;
  int	result;
  int	neg;

  result = 0;
  str = is_neg(str, &neg);
  while (*str != '\0')
    {
      if (*str < 48 || *str > 57)
	{
	  result = result * neg;
	  return (result);
	}
      else
	{
	  nb = *str - 48;
	  result = result * 10 + nb;
	}
      str = str + 1;
    }
  result = result * neg;
  return (result);
}

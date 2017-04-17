/*
** my_putnbr_float.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
**
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Wed Feb 15 09:33:08 2017 IRICANIN Filip
*/

#include "functions.h"

int	my_pow(int nb, int pow)
{
  int	p;
  int	result;

  p = 1;
  result = 1;
  if (pow < 0)
    return (0);
  if (pow == 0)
    return (1);
  while (p <= pow)
    {
      result = result * nb;
      p = p + 1;
    }
  return (result);
}

int   my_putnbr_float(float n, int d) {
    int i;
    int j;
    float k;

    k = n;
    i = 0;
    j = d;
    while ((n /= 10) >= 1)
      i++;
    my_put_nbr(n * my_pow(10, i + 1));
    k -= (int)k;
    while ((k *= 10) <= 1)
      j++;
    my_putchar('.');
    (j <= 0) ? (my_put_nbr(k * my_pow(10, j + 5))) : (my_put_nbr(k * my_pow(10, j - 1)));
    return (0);
}

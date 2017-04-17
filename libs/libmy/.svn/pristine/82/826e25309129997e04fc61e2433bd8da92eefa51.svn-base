/*
** my_putnbr_base_unsigned.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
**
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Fri Mar 6 17:47:14 2014 IRICANIN Filip
*/

#include "functions.h"

int		my_putnbr_base_unsigned(unsigned n, char *base)
{
  unsigned int	m;
  unsigned int	d;
  unsigned int	len;
  unsigned int	i;

  i = 0;
  len = my_strlen(base);
  d = 1;
  while ((n / d) >= len)
    d = d * len;
  while (d > 0) {
      m = (n / d) % len;
      my_putchar(base[m]);
      i++;
      d = d / len;
    }
  return (i);
}

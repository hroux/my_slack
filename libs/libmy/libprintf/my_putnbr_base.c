/*
** my_putnbr_base.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
**
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Fri Mar 6 17:47:14 2014 IRICANIN Filip
*/

#include "functions.h"

int     my_putnbr_base(int nbr, char *base)
{
  int   i;
  int   m;

  i =  my_strlen(base);
  if (nbr < 0)
    {
      nbr = -1 * nbr;
      my_putchar('-');
    }
  m = nbr % i;
  nbr = nbr / i;
  if (nbr > 0)
    {
      my_putnbr_base(nbr, base);
    }
  my_putchar(base[m]);
  return (nbr);
}

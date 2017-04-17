/*
** my_putnbr_unsigned.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
**
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Fri Mar 6 17:47:14 2014 IRICANIN Filip
*/

#include "functions.h"

int		my_putnbr_unsigned(unsigned int nb)
{
  if (nb >= 4294967295)
    return (0);
   if (nb == 0)
      my_putstr("0\b");
  if (nb >= 10) {
      my_put_nbr(nb / 10);
      my_put_nbr(nb % 10);
    }
  else if (nb <= 9)
      my_putchar(nb + 48);
  return (0);
}

/*
** my_put_nbr.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
**
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Fri Mar 6 17:47:14 2014 IRICANIN Filip
*/

#include "functions.h"

void    my_put_nbr(int n)
{
  if (n == -2147483648)
    {
      my_putstr("-2147483648");
    }
  if (n <= 9 && n >= 0)
    {
      my_putchar(n + '0');
    }
  if (n > 9 && n != -2147483648)
    {
      my_put_nbr(n / 10);
      my_put_nbr(n % 10);
    }
  if (n < 0 && n != -2147483648)
    {
      my_putchar('-');
      n = n * -1;
      if (n <= 9 && n >= 0)
        {
          my_put_nbr(n);
        }
      if (n > 9)
	{
	  my_put_nbr(n / 10);
	  my_put_nbr(n % 10);
	}
    }
}

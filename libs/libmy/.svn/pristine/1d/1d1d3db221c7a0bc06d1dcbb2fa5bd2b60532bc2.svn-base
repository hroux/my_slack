/*
** functions3.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
**
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Fri Mar 6 17:47:14 2014 IRICANIN Filip
*/

#include <stdlib.h>
#include <stdarg.h>
#include "functions.h"

int		my_ustr(va_list ap)
{
  char		*str;
  
  str = va_arg(ap, char *);
  while (*str) {
    if ((int)*str < 32 || (int)*str >= 127) {
      my_putstr("\\0");
      my_putnbr_base(*str, "01234567");
    }
    else 
      my_putchar(*str);
    str++;
  }
  return (0);
}

int		my_float(va_list ap) {
  float		f;
  
  f = va_arg(ap, double);
  my_putnbr_float(f, 0);
  return (0);
}

int		my_float_dec(va_list ap, int d) {
  float		f;
  
  f = va_arg(ap, double);
  my_putnbr_float(f, d);
  return (0);
}

int     my_arrond(va_list ap) {
  float f;

  f = va_arg(ap, double);
  if (get_dec(f) >= 5)
    my_putnbr_float((f + 0.001), 3);
  else
    my_putnbr_float(f, 3);
  return (0);
}

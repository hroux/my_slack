/*
** functions.c for  in /home/student/Rendu_printf
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

int		my_deci(va_list ap) {
  int		n;

  n = va_arg(ap, int);
  my_put_nbr(n);
  return (0);
}

int		my_str(va_list ap) {
  char		*str;
  
  str = va_arg(ap, char *);
  if (str == NULL) {
    my_putstr("(null)");
    return (1);
  }
  else
    my_putstr(str);
  return (0);
}

int		my_char(va_list ap) {
  char		c;
  
  c = (char)va_arg(ap , int);
  my_putchar(c);
  return (0);
}

int		my_hex(va_list ap) {
  unsigned int	n;
  
  n = va_arg(ap, unsigned int);
  my_putnbr_base(n, "0123456789abcdef");
  return (0);
}

int		my_HEX(va_list ap) {
  unsigned int	n;
  
  n = va_arg(ap, unsigned int);
  my_putnbr_base(n, "0123456789ABCDEF");
  return (0);
}

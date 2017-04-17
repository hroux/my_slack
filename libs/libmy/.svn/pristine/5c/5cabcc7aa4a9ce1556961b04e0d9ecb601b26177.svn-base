/*
** functions2.c for  in /home/student/Rendu_printf
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

int		my_octal(va_list ap) {
  int		n;

  n = va_arg(ap, unsigned int);
  my_putnbr_base(n, "01234567");
  return (0);
}

int		my_bin(va_list ap) {
  int		n;
  
  n = va_arg(ap, int);
  my_putnbr_base(n, "01");
  return (0);
}

int		my_unsigned(va_list ap) {
  unsigned int	n;
  
  n = va_arg(ap, unsigned int);
  my_putnbr_unsigned(n);
  return (0);
}

int		my_xhex(va_list ap) {
  void		*point;
  
  point = va_arg(ap, void *);
  my_putstr("0x");
  my_putnbr_base((unsigned long)point, "0123456789abcdef");
  return (0);
}

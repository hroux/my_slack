/*
** my_printf.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Wed Feb 15 04:11:06 2017 IRICANIN Filip
*/

#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "my_printf.h"
#include "functions.h"

int		my_printf(const char *str, ...) {
  va_list	ap;

  va_start(ap, str);
  if  (str == NULL)
    return (1);
  while (*str) {
    if (*str == '%') {
      if (*(str + 1) == '.' && *(str + 3) == 'f') {
	my_float_dec(ap, my_atoi(*(str + 2)));
	str += 3;
      }
      else {
	arg_format(ap, *(str + 1));
	str++;
      }
    }
    else
      my_putchar(*str);
    str++;
  }
  va_end(ap);
  return (0);
}

int		my_vprintf(const char *str, va_list ap)
{
  if (str == NULL)
    return (1);

  while (*str) {
    if (*str == '%') {
      if (*(str + 1) == '.' && *(str + 3) == 'f') {
	my_float_dec(ap, my_atoi(*(str + 2)));
	str += 3;
      }
      else {
	arg_format(ap, *(str + 1));
	str++;
      }
    }
    else
      my_putchar(*str);
    str++;
  }
  
  return (0);
}

int		arg_format(va_list ap, char c) {
  static t_form	formats[] = {{'d', &my_deci},
			     {'x', &my_hex},
			     {'i', &my_deci},
			     {'X', &my_HEX},
			     {'p', &my_xhex},
			     {'s', &my_str},
			     {'u', &my_unsigned},
			     {'o', &my_octal},
			     {'S', &my_ustr},
			     {'c', &my_char},
			     {'b', &my_bin},
			     {'f', &my_float},
			     {'F', &my_float},
			     {'g', &my_arrond},
			     {'G', &my_arrond},
			     {0, NULL}};
  
  check_format(ap, formats, c);
  return (0);
}


int		check_format(va_list ap, t_form formats[], char c) {
  int		i;
  int		done;
  
  done = 0;
  for (i = 0; formats[i].c != 0; i++) {
    if (formats[i].c == c) {
      formats[i].f(ap);
      done = 1;
    }
  }
  if (done == 0) {
    my_putchar('%');
    my_putchar(c);
  }
  return (0);
}

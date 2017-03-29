#ifndef _MY_PRINTF_H_
#define _MY_PRINTF_H_

#include <stdarg.h>

typedef struct	s_form
{
  char		c;
  int		(*f)(va_list p);
}	t_form;

#endif
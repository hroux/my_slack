/*
** functions.h for  in /root/libmy_extended
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:44:03 2017 IRICANIN Filip
** Last update Thu Feb 23 06:44:04 2017 IRICANIN Filip
*/
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdarg.h>
#include "my_printf.h"

int	my_deci(va_list ap);
int	my_str(va_list ap);
int	my_char(va_list ap);
int	my_printf(const char *str, ...);
int	my_vprintf(const char *str, va_list ap);
int	arg_format(va_list ap, char c);
int	check_format(va_list ap, t_form formats[], char c);
void	my_putchar(char c);
void    my_put_nbr(int n);
void	my_putstr(char *str);
int	my_hex(va_list ap);
int	my_HEX(va_list ap);
int     my_putnbr_base(int nbr, char *base);
int     my_strlen(char *str);
int	my_octal(va_list ap);
int	my_bin(va_list ap);
int	my_unsigned(va_list ap);
int	my_xhex(va_list ap);
int	my_putnbr_unsigned(unsigned int nb);
int	my_ustr(va_list ap);
int   	my_putnbr_float(float n, int d);
int 	my_float(va_list ap);
int 	my_float_dec(va_list ap, int d);
int   	my_atoi(char i);
int     my_arrond(va_list ap);
int	my_pow(int nb, int pow);
int     get_dec(double f);
#endif 

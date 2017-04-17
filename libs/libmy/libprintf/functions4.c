/*
** functions4.c for  in /home/student/Rendu_printf
**
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
**
** Started on  Tue Mar 3 09:57:06 2014 IRICANIN Filip
** Last update Fri Mar 6 17:47:14 2014 IRICANIN Filip
*/

int     get_dec(double f) {
  int   i;

  f -= (int)f;
  for (i = 0; i < 3; i++) {
    f *= 10;
    f -= (int)f;
  }
  return ((int)(f *= 10));
}

int   my_atoi(char i) {
  int   c;

  c = 0;
  c = i - '0'; 
  return (c);
}

/*
** misc.c for  in /root/libmy_extended/libparse
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:35:20 2017 IRICANIN Filip
** Last update Mon Apr 17 16:37:02 2017 ROUX Hugues
*/

char	*remove_all_chars(char* str, char c) {
  char	*pr;
  char	*pw;

  pr = str;
  pw = str;
  while (*pr)
    {
      *pw = *pr++;
      pw += (*pw != c);
    }
  *pw = '\0';
  return str;
}

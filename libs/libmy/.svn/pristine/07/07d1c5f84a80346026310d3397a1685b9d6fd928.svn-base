/*
** misc.c for  in /root/libmy_extended/libparse
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:35:20 2017 IRICANIN Filip
** Last update Thu Feb 23 06:35:21 2017 IRICANIN Filip
*/

char *remove_all_chars(char* str, char c) {

    char *pr = str;
    char *pw = str;

    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';

    return str;
}

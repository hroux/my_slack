/*
** msg.c for  in /home/hugues/Documents/C/my_slack/client
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Mon Apr 17 17:25:53 2017 ROUX Hugues
** Last update Tue Apr 25 00:20:44 2017 ROUX Hugues
*/
#include "includes/client.h"

/**
 * Fonction "générique" permettant d'envoyer un message
 * Attention : free le message en passant
 */
int	my_send(int sock, char *msg)
{
  int	n;

  if (msg == NULL)
    return 5;
  my_str_replace(msg, ' ', '|');
  n = send(sock, msg, my_strlen(msg) + 1, 0);
  free(msg);
  if (n < 0)
    return 6;
  else
    return -1;
}

/**
 * Fonction "générique" permettant de recevoir le message
 * Attention : free le message en passant
 */
int	my_recv(int sock, char *msg, int print)
{
  int	n;
  
  if (msg == NULL)
    return 5;
  if ((n = recv(sock, msg, 1023, 0)) < 0)
    return 7;
  if (n == 0)
    {
      msg[n] = '\0';
      my_str_replace(msg, '|', ' ');
      if (print == 1)
	my_printf("%s\n", msg);
      else
	Logger->debug(Logger,"%s\n", msg);
      free(msg);
      return 8;
    }
  msg[n] = '\0';
  my_str_replace(msg, '|', ' ');
  if (print == 1)
    my_printf("%s\n", msg);
  else
    Logger->debug(Logger,"%s \n", msg);
  free(msg);
  return -1;
}

/**
 * Un str_replace normal
 */
void	my_str_replace(char *str, char find, char replace)
{
  int	i;

  i = 0;
  if (str == NULL)
    return;
  while (str[i] != '\0')
    {
      if (str[i] == find)
	str[i] = replace;
      i++;
    }
}

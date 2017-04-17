/*
** msg.c for  in /home/hugues/Documents/C/my_slack/client
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Mon Apr 17 17:25:53 2017 ROUX Hugues
** Last update Mon Apr 17 20:14:25 2017 ROUX Hugues
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
  n = send(sock, msg, my_strlen(msg) + 1, 0);
  free(msg);
  if (n < 0)
    return 6;
  else
    return -1;
}

/**
 * Fonction "générique" permettant d'envoyer un message
 * Attention : free le message en passant
 */
/*int	my_recv(int sock, char *msg)
{
  if (msg == NULL)
    return 5;
  if ((n = recv(this->sock, msg, 1023, 0)) < 0)
    return 7;
  if (n == 0)
    {
      free(msg);
      return 8;
    }
    }*/
  

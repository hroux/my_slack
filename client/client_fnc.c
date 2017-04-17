/*
** client_fnc.c for  in /home/hugues/Documents/C/my_slack/client
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Sun Apr  9 22:36:18 2017 ROUX Hugues
** Last update Mon Apr 17 20:14:04 2017 ROUX Hugues
*/
#include "includes/client.h"

/**
 * Fonction permettant de lire un message 
 * sur stdin et de l'envoyer au serveur
 */
int	get_and_send_msg(t_client *this)
{
  char	*msg;
  int	result;
  
  msg = readLine();
  if (msg == NULL)
    return 5;
  if (my_strstr("/quit", msg) != NULL)
    {
      free(msg);
      return 0;
    }
  result = my_send(this->sock, msg);
  return result;
}

/**
 * Fonction permettant de lire un message 
 * envoyé et de le printer
 */
int	recv_and_print_msg(t_client *this)
{
  char	*msg;
  int	n;

  msg = malloc(sizeof(char) * 1024);
  if (msg == NULL)
    return 5;
  if ((n = recv(this->sock, msg, 1023, 0)) < 0)
    return 7;
  if (n == 0)
    {
      free(msg);
      return 8;
    }
  msg[n] = '\0';
  my_printf("%s\n", msg);
  free(msg);
  my_send(this->sock, my_strdup("OK Message recieved"));
  return -1;
}

/**
 * Fonction permettant d'initialiser le tableau des erreurs
 */
char		**init_error()
{
  static char	*tab_error[9];

  tab_error[0] = "Déconnection du client";
  tab_error[1] = "Création de socket impossible";
  tab_error[2] = "L'host n'existe pas";
  tab_error[3] = "Connection au serveur impossible";
  tab_error[4] = "Erreur select";
  tab_error[5] = "Erreur malloc";
  tab_error[6] = "Envoie du message impossible";
  tab_error[7] = "Reception du message impossible";
  tab_error[8] = "Serveur déconnecté";
  return (tab_error);
}

/**
 * Fonction permettant de printer l'erreur
 * en fonction du code en paramètre
 */
void		print_error(int code)
{
  char		**tab_error;
   
  if (code < 0 || code > 9)
    return;
  tab_error = init_error();
  if (code != 0)
    Logger->warn(Logger,"%s \n", tab_error[code]);
  else
    Logger->info(Logger,"%s \n", tab_error[code]);
}
  

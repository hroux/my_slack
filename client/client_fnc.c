/*
** client_fnc.c for  in /home/hugues/Documents/C/my_slack/client
**
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
**
** Started on  Sun Apr  9 22:36:18 2017 ROUX Hugues
** Last update Wed Apr 26 18:57:26 2017 VRIGNAUD camille
*/
#include "includes/client.h"

/*
 * Message received
 *
 * Fonction permettant de lire un message
 * sur stdin et de l'envoyer au serveur
 */
int	get_and_send_msg(t_client *this)
{
  char	*msg;
  int	result;

  result = -1;
  if ((msg = readLine()) == NULL)
    return 5;
  if (my_strcmp("quit", msg) == 0)
    {
      free(msg);
      return 0;
    }
  if (my_strcmp("help", msg) == 0)
    {
      free(msg);
      help();
    }
  else if (my_strlen(msg) != 0)
    {
      if ((result = my_send(this->sock, msg)) == -1)
	{
	  msg = malloc(sizeof(char) * 1024);
	  result = my_recv(this->sock, msg, 0);
	}
    }
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
  if ((n = my_recv(this->sock, msg, 1)) > 0)
    return n;
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

/*
 *Fonction permettant d'afficher la liste des commandes
 */
void	help()
{
  my_printf("/*********Help*********/\n");
  my_printf("join\t<name_salon>\tRejoindre un salon\n");
  my_printf("create\t<name_salon>\tCréer un salon\n");
  my_printf("delete\t<name_salon>\tSupprimer un salon\n");
  my_printf("list\t\t\tAfficher la liste des salons\n");
  my_printf("private\t<name_user>\tEnvoyer un message privé\n");
  my_printf("help\t\t\tAfficher l'aide\n");
  my_printf("quit\t\t\tSe déconnecter\n");
}

/*
** client.c for  in /home/hugues/Documents/C/my_slack/client
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Sun Apr  9 17:23:57 2017 ROUX Hugues
** Last update Mon Apr 17 17:07:43 2017 ROUX Hugues
*/
#include "includes/client.h"

/**
 * Fonction permettant de créer une structure client
 */
t_client	*create_client(){
  t_client	*client;

  client = malloc(sizeof(t_client));
  if (client == NULL)
    return NULL;
  client->free = free_client;
  client->start = start_client;
  client->go = go_client;
  client->error = print_error;
  client->sock = -1;
  client->ip = NULL;
  client->port = NULL;
  return client;
}

/**
 * Fonction permettant de free proprement un client
 */
void	free_client(t_client *client)
{
  if (client != NULL)
    {
      if (client->ip != NULL)
	free(client->ip);
      if (client->port != NULL)
	free(client->port);
      if (client->sock > 0)
	close(client->sock);
      free(client);
    }
}

/**
 * Fonction permettant de créer la connection au serveur
 * s'il y a erreur, on renvoit un chiffre >0
 */
int			init_client(t_client *this)
{
  int			sock;
  struct hostent	*hostinfo = NULL;
  struct sockaddr_in	serverSockAddr;
  int			size;

  hostinfo = NULL;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock == -1)
    return 1;
  this->sock = sock;
  hostinfo = gethostbyname(this->ip);
  if (hostinfo == NULL)
    return 2;
  this->serverSockAddr.sin_addr = *(struct in_addr*)hostinfo->h_addr;
  this->serverSockAddr.sin_port = htons(my_getnbr(this->port));
  this->serverSockAddr.sin_family = AF_INET;
  serverSockAddr = this->serverSockAddr;
  size = sizeof(serverSockAddr);
  if (connect(sock, (struct sockaddr *)&serverSockAddr, size) < 0 )
    return 3;
  return 0;
}

/**
 * Fonction permettant d'initialiser et de lancer le client
 * Si erreur alors il le log
 */
void		start_client(t_client *this)
{
  int		err;
  
  err = init_client(this);
  if (err > 0)
    {
      this->error(err);
      return;
    }
  err = this->go(this);
  this->error(err);
}

/**
 *Fonction réalisant une boncle inf 
 *pour envoyer et recevoir les messages
 */
int		go_client(t_client *this)
{
  fd_set	rdfs;
  int		n;

  n = -1;
  while (n == -1)
    {
      FD_ZERO(&rdfs);
      FD_SET(STDIN_FILENO, &rdfs);
      FD_SET(this->sock, &rdfs);
      if(select(this->sock + 1, &rdfs, NULL, NULL, NULL) == -1)
	return 4;
      if(FD_ISSET(STDIN_FILENO, &rdfs))
	n = get_and_send_msg(this);
      else if(FD_ISSET(this->sock, &rdfs))
	n = recv_and_print_msg(this);
    }
  return n;
}
    
  

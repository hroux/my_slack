/*
** client.h for  in /home/hugues/Documents/C/my_slack/client
** 
** Made by ROUX Hugues
** Login   <roux_a@etna-alternance.net>
** 
** Started on  Mon Apr 17 17:24:29 2017 ROUX Hugues
** Last update Tue Apr 25 00:20:05 2017 ROUX Hugues
*/

#ifndef __MY_SLACK_CLIENT_H__
#define __MY_SLACK_CLIENT_H__

#include "../../libs/libmy/libmy_extended.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef struct	s_client
{
  char			*ip;
  char			*port;
  void			(*free)(struct s_client*);
  void			(*start)(struct s_client*);
  void			(*error)(int code);
  int			(*go)(struct s_client*);
  int			sock;
  struct sockaddr_in	serverSockAddr;
}			t_client;

//Fonctions initialisation et deinitialisation
t_client	*create_client();
void		free_client(t_client *client);
int		init_client(t_client *this);

// Fonctions d'action
void		start_client(t_client *client);
int		go_client(t_client *this);
void		help();

// Fonction envoi et reception
int		recv_and_print_msg(t_client *this);
int		get_and_send_msg(t_client *this);
int		my_send(int sock, char *msg);
int		my_recv(int sock, char *msg, int print);
void		my_str_replace(char *msg, char find, char replace);

//Fonctions d'erreurs
void		print_error(int code);
char		**init_error();

//TODO à mettre dans la libmy
char		*my_strdup(char * str);
int		my_strlen(char *str);
char		*my_strcpy(char *dest, char *src);
int		my_strncmp(char *s1, char *s2, int n);
char		*my_strstr(char *str, char *to_find);
int		my_getnbr(char *str);
char		*readLine();
int		my_strcmp(char *s1, char *s2);

#endif // __MY_SLACK_CLIENT_H__

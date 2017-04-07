#ifndef __MY_SLACK_SERVER_H__
#define __MY_SLACK_SERVER_H__

#include "../../libs/libmy/libmy_extended.h"
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define PORT 8080
#define BACKLOG 512
#define PROTOCOL "TCP"
#define MSG_LENGTH 1024

typedef struct s_server {
    int 				listener;
    struct sockaddr_in 	addr;
	struct sockaddr_in 	cli;
    struct protoent 	*protocol;
    socklen_t 			socklen;
	t_list				*clients;
	fd_set				readfs;

    int (*start)();

} t_server;

typedef struct s_client {
	char	*name;
	int 	socket;
} t_client;

typedef struct s_message {
	char	*msg;
	char	*auteur;
	char	*cible;
	char	*commande;
} t_message;

t_server    *create_server();
void    server_init(t_server *);
int start_server(t_server *);
void create_client(t_server *);
int on_client_message(void *, void *);
int bind_client(void *, void *);
void broadcast_msg(t_server *, char *, t_client *);
void message_priver(t_server *this, char **msg, t_client *sender);
char	**my_str_to_wordtab(char *str);
int     Est_priver(char *buffer);
void    envoie_private(t_server *this, char *msg, t_client *sender);
char    *decode_msg(char *buffer);
int VerifMessage(char *buffer);
t_message *Create_message(char *buffer);

#endif // __MY_SLACK_SERVER_H__

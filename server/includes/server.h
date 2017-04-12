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
	t_list				*sallons;
	fd_set				readfs;

    int (*start)();

} t_server;

typedef struct s_sallon {
	char	*name;
	t_list	*clients;
} t_sallon;

typedef struct s_client {
	char	*name;
	t_sallon *sallon;
	int 	socket;
} t_client;

typedef struct s_message {
	char		*msg;
	t_client	*auteur;
	char		*cible;
	char		*commande;
} t_message;


t_server    *create_server();
void    server_init(t_server *);
int start_server(t_server *);
void create_client(t_server *);
int on_client_message(void *, void *);
int bind_client(void *, void *);
void broadcast_msg(t_server *, char *, t_client *);
char	**my_str_to_wordtab(char *str);
char    *decode_msg(char *buffer);
int VerifMessage(char *buffer);
t_message *Create_message(char *buffer, t_client *client);
void message_priver(t_server *this, t_message *message);
char **fill_commande();
t_sallon *init_sallon(t_message *message);
t_sallon *add_client(t_sallon *sallon, t_client *client);
t_sallon *del_client(t_sallon *sallon, t_client *client);
void msg_sallon(char *msg, t_client *sender, t_sallon *sallon);
int  type_commande(char *buffer);
t_server *server_fill(t_server *server);

#endif // __MY_SLACK_SERVER_H__

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
	t_list				*salons;
	fd_set				readfs;

    int (*start)();

} t_server;

typedef struct s_salon {
	char	*name;
	t_list	*clients;
} t_salon;

typedef struct s_client {
	char	*name;
	t_salon *salon;
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
t_salon *init_salon(t_message *message);
t_salon *add_client(t_salon *salon, t_client *client);
t_salon *del_client(t_salon *salon, t_client *client);
void msg_salon(char *msg, t_client *sender, t_salon *salon);
int  type_commande(char *buffer);
t_server *server_fill(t_server *server);
void	get_callback_msg(int sock);

#endif // __MY_SLACK_SERVER_H__

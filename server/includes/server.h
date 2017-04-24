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

typedef struct s_server t_server;
typedef struct s_client t_client;
typedef struct s_room t_room;
typedef struct s_message t_message;
typedef void (*t_handler)(t_server *, char *param, t_client *);

typedef struct s_server {
    int 				listener;
    struct sockaddr_in 	addr;
	struct sockaddr_in 	cli;
    struct protoent 	*protocol;
    socklen_t 			socklen;
	t_list				*clients;
	t_list				*rooms;
	fd_set				readfs;

    int     (*start)();
    void    (*broadcast)(struct s_server *, char *);
    void    (*terminate)(struct s_server *);
} t_server;

typedef struct s_room {
	char	*name;
	t_list	*clients;
    int     permanent;

	void (*add_client)(struct s_room *, t_client *);
	void (*remove_client)(struct s_room *, t_client *);
	void (*send)(char *, t_client *, t_room *);

} t_room;

typedef struct s_client {
	char	*name;
	t_room 	*room;
	int 	socket;
} t_client;

typedef struct s_message {
	char		*msg;
	t_client	*auteur;
	char		*cible;
	char		*commande;
} t_message;


typedef struct s_chat_cmd {
    char    *cmd;
    t_handler handler;
} t_chat_cmd;

// SERVER
t_server    *create_server();
void    terminate(t_server *);
void    server_init(t_server *);
int start_server(t_server *);
void create_client(t_server *);
int on_client_message(void *, void *);
int bind_client(void *, void *);
void broadcast_msg(t_server *, char *);
char	**my_str_to_wordtab(char *str);
char    *decode_msg(char *buffer);
int VerifMessage(char *buffer);
t_message *Create_message(char *buffer, t_client *client);
void message_priver(t_server *this, t_message *message);
char **fill_commande();

// ROOM
t_room	*create_room(char *, int);
void 	init_room(t_room *);
void	add_client(t_room *, t_client *);
void	remove_client(t_room *, t_client *);
void 	msg_salon(char *, t_client *, t_room *);


//MESSAGE
void    handle_message(t_server *, char *, t_client *);

//COMMANDS
void    join_room_cmd(t_server *, char *, t_client *);
void    create_room_cmd(t_server *, char *, t_client *);
void    delete_room_cmd(t_server *, char *, t_client *);
void    show_rooms_cmd(t_server *, char *, t_client *);

int  type_commande(char *buffer);

t_server *server_fill(t_server *server);
void	get_callback_msg(int sock);

// UTILS
t_list_item *get_client_node(t_list *, t_client *);
t_room *get_room_by_name(t_list *rooms, char *name);
t_list_item *get_room_node(t_list *, t_room *);

// FREE
//int free_client(void *node, void *arg);
//int free_room(void *node, void *arg);
void free_client(void *);
void free_room(void *);

#endif // __MY_SLACK_SERVER_H__

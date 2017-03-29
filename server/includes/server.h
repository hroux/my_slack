#ifndef __MY_SLACK_SERVER_H__
#define __MY_SLACK_SERVER_H__

#include "../../libs/libmy/libmy_extended.h"
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>

#define PORT 8080
#define BACKLOG 512
#define PROTOCOL "TCP"
#define MSG_LENGTH 1024

typedef struct s_server {
    int listener;
    struct sockaddr_in addr;
	struct sockaddr_in cli;
    struct protoent *protocol;
    socklen_t socklen;
	t_list	*clients;

    void (*start)();

} t_server;

typedef struct s_client {
	char	*name;
	int 	socket;
} t_client;

t_server    *create_server();
void    server_init(t_server *);
void start_server(t_server *);

#endif // __MY_SLACK_SERVER_H__

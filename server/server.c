#include <memory.h>
#include "includes/server.h"

t_server    *create_server() {

    t_server *server;

    server = malloc(sizeof(t_server));
    if (server == NULL) {
        return NULL;
    }
    server->socklen = sizeof(server->addr);
    server->protocol = getprotobyname(PROTOCOL);
    if (server->protocol == NULL) {
        return NULL;
    }
    server->listener = socket(AF_INET, SOCK_STREAM, server->protocol->p_proto);
    if (server->listener == -1) {
        return NULL;
    }
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_port = htons(PORT);
    if (bind(server->listener, (const struct sockaddr*) &server->addr, sizeof(server->addr)) ==- 1) {
        return NULL;
    }
    if (listen(server->listener, BACKLOG) == -1) {
        return NULL;
    }
    server_init(server);

    return (server);
}

void    server_init(t_server *this) {
    this->clients = create_list(sizeof(t_client), NULL);
    this->start = start_server;
}

void start_server(t_server *this) {
    char        buffer[MSG_LENGTH];
    t_client    *client;
    int         n;

    my_printf("Starting Slack server !\n");

    client = malloc(sizeof(t_client));
    client->socket = accept(this->listener, (struct sockaddr *)&this->cli, &this->socklen);
    client->name = NULL;

    if (client->socket == -1) {
        my_printf("Failed to create client\n");
        return;
    }

    this->clients->push(this->clients, client);
    send(client->socket, "Connected\n", strlen("Connected\n"), 0);

    while (1) {
        if (client->name == NULL) {
            send(client->socket, "Enter your name : ", strlen("Enter your name : "), 0);
            n = recv(client->socket, buffer, sizeof(buffer), 0);
            buffer[n-1] = '\0';
            client->name = strdup(buffer);
        }
        else {
            n = recv(client->socket, buffer, sizeof(buffer), 0);
            buffer[n] = '\0';
            my_printf("Message from %s => %s", client->name, buffer);
        }
    }
}
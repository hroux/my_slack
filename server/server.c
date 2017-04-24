#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

t_server *create_server() {

    t_server *server;

    server = malloc(sizeof(t_server));
    if (server == NULL) {
        return NULL;
    }
    server->socklen = sizeof(server->addr);
    server->protocol = getprotobyname(PROTOCOL);
    if (server->protocol == NULL) {
        free(server);
        return NULL;
    }
    server->listener = socket(AF_INET, SOCK_STREAM, server->protocol->p_proto);
    if (server->listener == -1) {
        free(server);
        return NULL;
    }
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_port = htons(PORT);
    if (bind(server->listener, (const struct sockaddr *) &server->addr, sizeof(server->addr)) == -1) {
        free(server);
        return NULL;
    }
    if (listen(server->listener, BACKLOG) == -1) {
        free(server);
        return NULL;
    }
    server_init(server);
    return (server);
}

void server_init(t_server *this) {
    t_room *general;

    this->rooms = create_list(sizeof(t_room), free_room);
    this->clients = create_list(sizeof(t_client), free_client);
    this->start = start_server;
    this->terminate = terminate;
    this->broadcast = broadcast_msg;
    general = create_room(strdup("general"), TRUE);
    this->rooms->push(this->rooms, general);
    free(general);
}


int start_server(t_server *this) {
    int fds;

    my_printf("Slack server started successfully !\n");
    while (1) {
        FD_ZERO(&this->readfs);
        FD_SET(0, &this->readfs);
        FD_SET(this->listener, &this->readfs);
        this->clients->for_each(this->clients, bind_client, this);
        my_printf("Number of clients => %d\n", this->clients->size);
        fds = select(4 + this->clients->size, &this->readfs, NULL, NULL, NULL);
        my_printf("File descriptors => %d\n", fds);
        if (FD_ISSET(this->listener, &this->readfs)) {
            create_client(this);
            FD_CLR(this->listener, &this->readfs);
        }
        if (FD_ISSET(0, &this->readfs)) {
            this->terminate(this);
            close(4);
            return (EXIT_SUCCESS);
        }
        this->clients->for_each(this->clients, on_client_message, this);
    }
}

int bind_client(void *server, void *node) {
    t_client *c;
    t_server *s;

    c = (t_client *) ((t_list_item *) node)->data;
    s = (t_server *) server;
    FD_SET(c->socket, &s->readfs);
    return 1;
}

/**
 * hroux : Rajout d'une réception après le send pour recevoir le "OK message receiv"
 */
void create_client(t_server *this) {

    t_room *general;
    t_client *new_client;
    char connect_msg[64];
    char buffer[32];
    int n;

    general = (t_room *) this->rooms->head->data;
    new_client = malloc(sizeof(t_client));
    if (new_client == NULL) {
        return;
    }
    new_client->name = NULL;
    new_client->socket = accept(this->listener, (struct sockaddr *) &this->cli, &this->socklen);
    if (new_client->socket < 0) {
        free(new_client);
        return;
    }
    send(new_client->socket, "Welcome to my slack !\n", strlen("Welcome to my slack !\n"), 0);
    get_callback_msg(new_client->socket);
    send(new_client->socket, "Enter your name : ", strlen("Enter your name : "), 0);
    get_callback_msg(new_client->socket);
    n = recv(new_client->socket, buffer, sizeof(buffer), 0);
    buffer[n - 1] = '\0';
    new_client->name = strdup(buffer);
    new_client->room = general;
    general->add_client(general, new_client);
    my_printf("Created new client with id => %d\n", new_client->socket);
    sprintf(connect_msg, "User %s connected\n", new_client->name);
    this->clients->push(this->clients, new_client);
    broadcast_msg(this, connect_msg);
    free(new_client);
}

int on_client_message(void *server, void *node) {
    char buffer[MSG_LENGTH];
    char deco_msg[128];
    int n;
    t_server *s;
    t_client *c;

    s = (t_server *) server;
    c = (t_client *) ((t_list_item *) node)->data;

    if (FD_ISSET(c->socket, &s->readfs)) {
        my_printf("Message from %s\n", c->name);
        n = recv(c->socket, buffer, sizeof(buffer), 0);
        if (n == 0 || n == -1) {
            my_printf("User %s disconnected\n", c->name);
            sprintf(deco_msg, "User %s disconnected\n", c->name);
            c->room->remove_client(c->room, c);
            s->clients->remove(s->clients, get_client_node(s->clients, c), 1);
            close(c->socket);
            broadcast_msg(s, deco_msg);
            return 1;
        }
        buffer[n] = '\0';
        my_printf("Message => %s\n", buffer);
        handle_message(s, buffer, c);
        FD_CLR(c->socket, &s->readfs);
    }
    return 1;
}

/**
 * hroux : Rajout d'une réception après un send pour recevoir le "OK message receiv"
 * iricanf: Correction du broadcast, la fonction permet d'envoyer un message dans tous les salons du serveur
 */
void broadcast_msg(t_server *this, char *msg) {
    t_list_item *room_node;
    t_list_item *client_node;
    t_room *room;
    t_client *client;

    room_node = this->rooms->head;
    while (room_node != NULL) {

        room = (t_room *) room_node->data;
        client_node = room->clients->head;
        while (client_node != NULL) {
            client = (t_client *) client_node->data;
            send(client->socket, msg, strlen(msg), 0);
            get_callback_msg(client->socket);
            client_node = client_node->next;
        }

        room_node = room_node->next;
    }
}

/**
 * hroux : Rajout d'une réception après le send pour recevoir le "OK message receiv"
 */
void message_priver(t_server *this, t_message *message) {
    char *full_msg;
    t_list_item *tmp;
    t_client *test;
    t_client *client;

    tmp = this->clients->head;
    if (strcmp(message->commande, "private") == 0) {
        while (tmp != NULL) {
            test = (t_client *) tmp->data;
            if (strcmp(test->name, message->cible) == 0)
                client = test;
            tmp = tmp->next;
        }
        if (client->socket > 0) {
            full_msg = malloc(sizeof(char) * (strlen(message->auteur->name) + strlen(message->msg) + 1));
            sprintf(full_msg, "%s : %s\n", message->auteur->name, message->msg);
            send(client->socket, full_msg, strlen(full_msg), 0);
            get_callback_msg(client->socket);
        } else {
            send(message->auteur->socket, "Désolé mais cet utilisateur n'est pas connecté\n", 48, 0);
            get_callback_msg(message->auteur->socket);
        }
    }
}

/**
 *fonction permettant de recevoir le "OK Message receved du client"
 *à mettre après chaque send
 *
 */
void get_callback_msg(int sock) {
    char *rep_client;
    int n;

    if ((rep_client = malloc(sizeof(char) * 1024)) != NULL) {
        n = recv(sock, rep_client, 1023, 0);
        rep_client[n] = '\0';
        my_printf("%s\n", rep_client);
        free(rep_client);
    }
}
  

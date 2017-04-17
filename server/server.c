#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
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
    server = server_fill(server);
    server_init(server);
    return (server);
}

void    server_init(t_server *this) {
    this->start = start_server;
}

t_server *server_fill(t_server *server)
{
    t_salon *salon;
    t_message *message;

    server->clients = create_list(sizeof(t_client), NULL);
    server->salons = create_list(sizeof(t_salon), NULL);
    message = malloc(sizeof(t_message));
    //message->cible = malloc(sizeof(char *));
    message->cible = strdup("general");
    salon = init_salon(message);
    server->salons->push(server->salons, salon);
    return (server);
}

int start_server(t_server *this) {
    int         fds;

    my_printf("Slack server running...\n");
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
        if (FD_ISSET(0, &this->readfs))
        {
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
void		create_client(t_server *this) {
  t_client	*new_client;
  char		connect_msg[64];
  char		buffer[32];
  int		n;	

  new_client = malloc(sizeof(t_client));
  if (new_client == NULL) {
    return;
  }
  new_client->name = NULL;
  new_client->socket = accept(this->listener, (struct sockaddr *)&this->cli, &this->socklen);
  if (new_client->socket < 0) {
    free(new_client);
    return;
  }
  send(new_client->socket, "Welcome to my slack !\n", strlen("Welcome to my slack !\n"), 0);
  get_callback_msg(new_client->socket);
  send(new_client->socket, "Enter your name : ", strlen("Enter your name : "), 0);
  get_callback_msg(new_client->socket);
  n = recv(new_client->socket, buffer, sizeof(buffer), 0);
  buffer[n-1] = '\0';
  new_client->name = strdup(buffer);
  new_client->salon = this->salons->head->data;
  add_client(this->salons->head->data, new_client);
  my_printf("Created new client with id => %d\n", new_client->socket);
  sprintf(connect_msg, "User %s connected\n", new_client->name);
  this->clients->push(this->clients, new_client);
  broadcast_msg(this, connect_msg, NULL);
}

int on_client_message(void *server, void *node) {
    t_list_item *tmp1;
    t_salon *test;
    char        buffer[MSG_LENGTH];
    t_message   *message;
    t_salon    *salon;
    char        deco_msg[128];
    int         n;
    t_server    *s;
    t_client    *c;
    t_list_item    *client;
    s = (t_server *) server;
    c = (t_client *) ((t_list_item *) node)->data;
    if (FD_ISSET(c->socket, &s->readfs)) {
        my_printf("Message from %s\n", c->name);
        n = recv(c->socket, buffer, sizeof(buffer), 0);
        if (n == 0 || n == -1) {
            my_printf("User %s disconnected\n", c->name);
            sprintf(deco_msg, "User %s disconnected\n", c->name);
            tmp1 = s->salons->head->data;
                test = (t_salon *) tmp1;
               client =  test->clients->head;
                //del_client(s->salons->head->data, c);
                test->clients->remove(test->clients, client);
            close(c->socket);
            broadcast_msg(s, deco_msg, NULL);
            return 1;
        }
        buffer[n] = '\0';
        my_printf("Message => %s\n", buffer);
        if (type_commande(buffer) == 1)
        {
           message = Create_message(buffer, c);
           message_priver(s, message);
        }
        else if(type_commande(buffer) == 2)
        {
            my_printf("mode salon");
            message = Create_message(buffer, c);
            salon = init_salon(message);
            //salon = add_client(salon, c);
            //s->salons->head->data =  del_client(s->salons->head->data, c);
            //s->salons->push(s->salons, salon);
            my_printf("Name of salon : %s\n", salon->name);
        }
        else
            broadcast_msg(s, buffer, c);
        FD_CLR(c->socket, &s->readfs);
    }
    return 1;
}

/**
 * hroux : Rajout d'une réception après un send pour recevoir le "OK message receiv"
 */
void		broadcast_msg(t_server *this, char *msg, t_client *sender) {
  t_list_item	*tmp;
  t_list_item	*tmp1;
  t_client	*client;
  char		*full_msg;
  t_salon	*test;

  tmp1 = this->salons->head;
  test = (t_salon *) tmp1->data;
  while (tmp1 != NULL)
    {
      tmp = test->clients->head;
      if (tmp == NULL)
        return;
      if (sender != NULL) {
	//full_msg = malloc(sizeof(char) * (strlen(sender->name) +  strlen(msg) + 2));
	full_msg = malloc(sizeof(char) * 1024);
	sprintf(full_msg, "%s : %s", sender->name, msg);
      }
      else
        full_msg = msg;
      while (tmp != NULL) {
        client = (t_client *) tmp->data;
        if (client != sender) {
	  send(client->socket, full_msg, strlen(full_msg), 0);
	  get_callback_msg(client->socket);
        }
        tmp = tmp->next;
      }
      tmp1 = tmp1->next;
    }
}

/**
 * hroux : Rajout d'une réception après le send pour recevoir le "OK message receiv"
 */
void message_priver(t_server *this, t_message *message) {
  char *full_msg;
  t_list_item *tmp;
  t_client    *test;
  t_client    *client;

  tmp = this->clients->head;
  if (strcmp(message->commande, "private") == 0)
    {
      while (tmp != NULL)
	{
	  test = (t_client *) tmp->data;
	  if (strcmp(test->name, message->cible) == 0)
            client = test;
	  tmp = tmp->next;
	}
      if (client->socket > 0)
	{
	  full_msg = malloc(sizeof(char) * (strlen(message->auteur->name) + strlen(message->msg) + 1));
	  sprintf(full_msg, "%s : %s\n", message->auteur->name, message->msg);
	  send(client->socket, full_msg, strlen(full_msg), 0);
	  get_callback_msg(client->socket);
	}
      else
	{
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
void	get_callback_msg(int sock)
{
  char	*rep_client;
  int	n;
  
  if ((rep_client = malloc(sizeof(char) * 1024)) != NULL)
    {
      n = recv(sock, rep_client, 1023, 0);
      rep_client[n] = '\0';
      my_printf("%s\n", rep_client);
      free(rep_client);
    }
}
  

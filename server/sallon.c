#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

t_sallon *init_sallon(char *name)
{
	t_sallon	*sallon;
	sallon = malloc(sizeof(sallon));
	if (sallon == NULL)
		return NULL;
	sallon->name = malloc(sizeof(name));
	if (sallon->name == NULL)
		return NULL;
	sallon->name = name;
	sallon->clients = create_list(sizeof(t_client), NULL);
	return sallon;
}

t_sallon *add_client(t_sallon *sallon, t_client *client, t_server *server)
{
	char *connect_msg;

	connect_msg = malloc(sizeof(char *));
	if (connect_msg == NULL)
		return NULL;
	sallon->clients->push(sallon->clients, client);
	my_printf("%s vient de rentrer dans le salon => %s\n", client->name, sallon->name);
	sprintf(connect_msg, "User %s connected to %s\n", client->name, sallon->name);
	broadcast_msg(server, connect_msg, NULL);

	return sallon;
}

t_sallon *del_client(t_sallon *sallon, t_client *client, t_server *server)
{
	char *connect_msg;

	connect_msg = malloc(sizeof(char *));
	if (connect_msg == NULL)
		return NULL;
	sallon->clients->remove(sallon->clients,  (t_list_item *)client);
	my_printf("%s vient de quitter le salon => %s\n", client->name, sallon->name);
	sprintf(connect_msg, "User %s disconnected to %s\n", client->name, sallon->name);
	broadcast_msg(server, connect_msg, NULL);

	return sallon;
}

void msg_sallon(char *msg, t_client *sender, t_sallon *sallon) {
    t_list_item *tmp;
    t_client    *client;
    char        *full_msg;

    tmp = sallon->clients->head;
    if (tmp == NULL)
        return;
    if (sender != NULL) {
        full_msg = malloc(sizeof(char) * (strlen(sender->name) +  strlen(msg)));
        sprintf(full_msg, "%s : %s", sender->name, msg);
    }
    else
        full_msg = msg;
    while (tmp != NULL) {
        client = (t_client *) tmp->data;
        if (client != sender) {
            send(client->socket, full_msg, strlen(full_msg), 0);
        }
        tmp = tmp->next;
    }
}
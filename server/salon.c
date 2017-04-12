#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

t_salon *init_salon(t_message *message)
{
	t_salon	*salon;
	
	salon = malloc(sizeof(t_salon));
	if (salon == NULL)
		return NULL;
	salon->name = malloc(sizeof(message->cible));
	if (salon->name == NULL)
		return NULL;
	salon->name = message->cible;
	salon->clients = create_list(sizeof(t_client), NULL);
	return salon;
}

t_salon *add_client(t_salon *salon, t_client *client)
{
	char *connect_msg;
	
	my_printf("ici add_client %s\n", salon->name);
	connect_msg = malloc(1024 *sizeof(char *));
	if (connect_msg == NULL)
		return NULL;
	client->salon = salon;
	salon->clients->push(salon->clients, client);
	my_printf("%s vient de rentrer dans le salon => %s\n", client->name, salon->name);
	sprintf(connect_msg, "User %s connected to %s\n", client->name, salon->name);
	msg_salon(connect_msg, client, salon);

	return salon;
}

t_salon *del_client(t_salon *salon, t_client *client)
{
	char *connect_msg;

	connect_msg = malloc(sizeof(char *));
	if (connect_msg == NULL)
		return NULL;
	my_printf("%d \n", salon->clients->size);
	salon->clients->remove(salon->clients,  (t_list_item *)client);
	my_printf("%d \n", salon->clients->size);
	my_printf("%s vient de quitter le salon => %s\n", client->name, salon->name);
	sprintf(connect_msg, "User %s disconnected to %s\n", client->name, salon->name);
	msg_salon(connect_msg, client, salon);

	return salon;
}

void msg_salon(char *msg, t_client *sender, t_salon *salon) {
    t_list_item *tmp;
    t_client    *client;
    char        *full_msg;

    tmp = salon->clients->head;
    if (tmp == NULL)
        return;
    if (sender != NULL) {
        full_msg = malloc(sizeof(char * ) * (strlen(sender->name) +  strlen(msg)));
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

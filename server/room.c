#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

t_room *create_room(char *name)
{
	t_room	*room;
	
	room = malloc(sizeof(t_room));
	if (room == NULL)
		return NULL;
	room->name = malloc(sizeof(name));
	if (room->name == NULL)
		return NULL;
	room->name = name;
	init_room(room);
	return (room);
}

void init_room(t_room *this) {
	this->clients = create_list(sizeof(t_client), NULL);
	this->add_client = add_client;
	this->remove_client = remove_client;
	this->send = msg_salon;
}

void add_client(t_room *this, t_client *client)
{
	char *connect_msg;
	
	//my_printf("ici add_client %s\n", salon->name);
	connect_msg = malloc(1024 *sizeof(char *));
	if (connect_msg == NULL)
		return;
	client->room = this;
	this->clients->push(this->clients, client);
	my_printf("%s vient de rentrer dans le salon => %s\n", client->name, this->name);
	sprintf(connect_msg, "User %s joined the room\n", client->name);
	msg_salon(connect_msg, client, this);
}

void remove_client(t_room *this, t_client *client)
{
	char *connect_msg;

	connect_msg = malloc(sizeof(char *));
	if (connect_msg == NULL)
		return;
	my_printf("%d \n", this->clients->size);
	my_printf("%s vient de quitter le salon => %s\n", client->name, this->name);
	sprintf(connect_msg, "User %s disconnected to %s\n", client->name, this->name);
    this->clients->remove(this->clients,  this->clients->find(this->clients, client));
    my_printf("%d \n", this->clients->size);
    this->send(connect_msg, NULL, this);
}

void msg_salon(char *msg, t_client *sender, t_room *room) {
    t_list_item *tmp;
    t_client    *client;
    char        *full_msg;

    tmp = room->clients->head;
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
	    get_callback_msg(client->socket);
        }
        tmp = tmp->next;
    }
}

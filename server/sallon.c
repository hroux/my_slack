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
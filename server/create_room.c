#include <memory.h>
#include <string.h>
#include "includes/server.h"

t_room		*create_room(char *name, int permanent) {
  t_room	*room;

  room = malloc(sizeof(t_room));
  if (room == NULL)
    return NULL;
  room->name = name;
  room->permanent = permanent;
  init_room(room);
  return (room);
}

void init_room(t_room *this) {
  this->clients = create_list(sizeof(t_client), free_client);
  this->add_client = add_client;
  this->remove_client = remove_client;
  this->send = msg_salon;
}

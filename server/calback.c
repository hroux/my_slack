#include <memory.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>
#include "includes/server.h"

/**
 *fonction permettant de recevoir le "OK Message receved du client"
 *à mettre après chaque send
 *TODO : logger les message en debbug
 */
void	get_callback_msg(int sock) {
  char	*rep_client;
  int	n;

  if ((rep_client = malloc(sizeof(char) * 1024)) != NULL)
    {
      n = recv(sock, rep_client, 1023, 0);
      if (n > 0)
	{
	  rep_client[n] = '\0';
	  my_printf("%s\n", rep_client);
	}
      free(rep_client);
    }
}

/**
 *fonction permettant de send le "OK Message receved au client"
 *à mettre après chaque send
 *TODO : test si no error + logger
 */
void	send_callback_msg(int sock) {
  char	*rep_client;

  if ((rep_client = my_strdup("OK|Message|received")) != NULL)
    {
      send(sock, rep_client, my_strlen(rep_client), 0);
      free(rep_client);
    }
}

void fill_server(t_server *server) {
  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = INADDR_ANY;
  server->addr.sin_port = htons(PORT);
}

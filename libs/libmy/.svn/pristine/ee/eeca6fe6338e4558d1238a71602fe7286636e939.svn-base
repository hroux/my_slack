#include <stdlib.h>
#include "../libmy_extended.h"
#include "headers/liblog.h"

t_logger *Logger;

int main()
{
  t_log_cfg	*config;

  config = malloc(sizeof(t_log_cfg));
  config->level = LEVEL_WARN;
  config->logfile = "./journal.log";
  
  Logger = create_logger(config);
  
  if (Logger != NULL)
    my_printf("Logger is initialized\n");

  Logger->debug(Logger, "This is a %s message !\n", "debug");
  Logger->info(Logger, "This is a %s message !\n", "info");
  Logger->error(Logger, "This is a %s message !\n", "error");
  Logger->warn(Logger, "This is a %s message !\n", "warning");

  Logger->free(Logger);
}

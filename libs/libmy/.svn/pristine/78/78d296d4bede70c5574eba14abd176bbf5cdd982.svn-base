#include <stdlib.h>
#include "multicopy.h"

t_logger *Logger;

int main(int argc, char **argv) {

  t_mcopy *mcopy = create_mcopy(argc, argv);
  t_option_field fields[] = {
    {"dest", "d", "Set the copy destination folder", "./", 1, 1, 0, NULL},
    {NULL, NULL, NULL, NULL, 0, 0, 0, NULL}
  };

  // fields = {
  //  {"dest", "d", "Set the copy destination folder", "./", 1, 1, 0, NULL}
  //};
  
  Logger = create_logger(NULL);

  if (!mcopy->parser->validate(mcopy->parser, fields)) {
    Logger->error(Logger, "Option 'dest' was not specified\n");
    Logger->free(Logger);
    mcopy->free(mcopy);
    return (1);
  }
  
  mcopy->start(mcopy);
  mcopy->free(mcopy);
  Logger->free(Logger);
}

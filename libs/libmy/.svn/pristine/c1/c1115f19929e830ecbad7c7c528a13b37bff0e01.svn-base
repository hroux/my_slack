/*
** copy.c for  in /root/libmy_extended/bonus
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:40:24 2017 IRICANIN Filip
** Last update Thu Feb 23 06:40:38 2017 IRICANIN Filip
*/
#include <stdio.h>
#include <stdlib.h>
#include "multicopy.h"

int		copy_file(char *src, char *dest)
{
  char	c;
  FILE *source;
  FILE *destination;

  source = fopen(src, "r");
  destination = fopen(dest, "w");

  if (source == NULL) {
    Logger->error(Logger, "The file %s does not exists\n", src);
    return (-1);
  }

  if (destination == NULL) {
    fclose(source);
    Logger->error(Logger, "Failed to create %s file\n", dest);
    return (-1);
  }

  while ( (c = fgetc(source)) != EOF ) {
    fputc(c, destination);
  }

  fclose(source);
  fclose(destination);

  Logger->info(Logger, "Successfully copied file %s\n", src);
  return (0);
}

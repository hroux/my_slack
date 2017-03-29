/*
** liblog.h for liblog in /root/Projets/libmy_extended/liblog
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Wed Feb  8 06:02:54 2017 IRICANIN Filip
** Last update Thu Feb 23 06:43:39 2017 IRICANIN Filip
*/
#ifndef __LIBLOG_H__
#define __LIBLOG_H__

#include <stdio.h>

#define LEVEL_DEBUG "debug"
#define LEVEL_INFO "info"
#define LEVEL_WARN "warning"
#define LEVEL_ERROR "error"

typedef struct s_log_cfg {
  char	*level;
  char	*logfile;
} t_log_cfg;

typedef struct s_loglevel {
  char	*name;
  int	weight;
} t_loglevel;

typedef struct s_logger {
  t_loglevel	*level;
  FILE		*logfile;

  void (*debug)(struct s_logger *, char *, ...);
  void (*info)(struct s_logger *, char *, ...);
  void (*warn)(struct s_logger *, char *, ...);
  void (*error)(struct s_logger *, char *, ...);
  void (*free)(struct s_logger *);
  
} t_logger;

extern t_logger *Logger;

// Logger
t_logger	*create_logger(t_log_cfg *);
void		init_logger(t_logger *, t_log_cfg *);
void		free_logger(t_logger *);
void		debug(t_logger *, char *, ...);
void		info(t_logger *, char *, ...);
void		warning(t_logger *, char *, ...);
void		error(t_logger *, char *, ...);

// Loglevel
t_loglevel      *get_loglevel(char *);

// Configuration
t_log_cfg       *get_default_cfg();

#endif

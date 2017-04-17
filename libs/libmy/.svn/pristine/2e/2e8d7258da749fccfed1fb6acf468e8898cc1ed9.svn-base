/*
** parser.h for  in /root/libmy_extended/libparse
** 
** Made by IRICANIN Filip
** Login   <irican_f@etna-alternance.net>
** 
** Started on  Thu Feb 23 06:43:09 2017 IRICANIN Filip
** Last update Thu Feb 23 06:43:18 2017 IRICANIN Filip
*/
#ifndef __PARSER_H__
#define __PARSER_H__

#include "../../liblist/headers/list.h"

typedef void (*t_option_callback)(void *);

typedef struct s_option {
    char *name;
    t_list *values;
} t_option;

typedef struct s_option_field {
    char *name;
    char *shortcut;
    char *description;
    char *default_value;

    int has_value;
    int required;
    int multiple_values;

    t_option_callback callback;
} t_option_field;

typedef struct s_parser {
    int argc;
    char **argv;
    t_list  *args;
    t_list  *options;

    int(*parse)(struct s_parser*);
    int(*validate)(struct s_parser *, t_option_field[]);
    void(*free)(struct s_parser *);

} t_parser;

t_parser *create_parser(int, char **);
void parse_args(t_parser *);
void parse_options(t_parser *this);
int validate(t_parser *this, t_option_field fields[]);

// Arguments functions
int is_option_value(t_parser *this, int index);

// Options functions
char *remove_all_chars(char* str, char c);
void get_opt_values(t_parser *, t_option *, int);
t_option *find_option_by_name(t_list *options, char *name);

// Free functions
void free_arg(void *arg);
void free_opt(void *opt);
void free_parser(t_parser *this);
int free_opt_values(void *, void *);

// Misc
int is_option(char *arg);

#endif //__PARSER_H__

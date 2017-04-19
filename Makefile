##
## Makefile for  in /home/hugues/Documents/C/my_slack
## 
## Made by ROUX Hugues
## Login   <roux_a@etna-alternance.net>
## 
## Started on  Mon Apr 17 17:38:47 2017 ROUX Hugues
## Last update Wed Apr 19 10:34:57 2017 ROUX Hugues
##

CC		=	gcc
SERVER_NAME	=	slack_server
CLIENT_NAME	=	slack_client

CFLAGS		=	-Wall -Wextra -Werror -g
LIBS		=	libs/libmy/libmy_extended.a

SERVER_SRC	=	server/main.c \
			server/my_str_to_wordtab.c \
			server/my_strlen.c \
			server/server.c \
			server/message.c \
			server/salon.c \
			server/my_strncpy.c\
			server/my_strchr.c

CLIENT_SRC	=	client/main.c \
			client/client.c \
			client/my_strlen.c\
			client/my_strdup.c \
			client/my_strcpy.c \
			client/my_strstr.c \
			client/my_strncmp.c \
			client/my_getnbr.c \
			client/readline.c \
			client/client_fnc.c \
			client/msg.c \
			client/my_strcmp.c

SERVER_OBJ	=	$(SERVER_SRC:%.c=%.o)
CLIENT_OBJ	=	$(CLIENT_SRC:%.c=%.o)

RM		=	rm -rf


ALL	:	server client


server	:	$(SERVER_OBJ)
		$(CC) $(SERVER_OBJ) $(LIBS) -o $(SERVER_NAME) $(CFLAGS)

client	:	$(CLIENT_OBJ)
		$(CC) $(CLIENT_OBJ) $(LIBS) -o $(CLIENT_NAME) $(CFLAGS)

clean	:
		$(RM) $(SERVER_OBJ)
		$(RM) $(CLIENT_OBJ)

fclean	:	clean
		$(RM) $(SERVER_NAME)
		$(RM) $(CLIENT_NAME)

re	:	fclean ALL

.PHONY	:	fclean

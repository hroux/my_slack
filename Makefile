##
## Makefile for  in /home/hugues/Documents/C/my_slack
##
## Made by ROUX Hugues
## Login   <roux_a@etna-alternance.net>
##
## Started on  Mon Apr 17 17:38:47 2017 ROUX Hugues
## Last update Mon Apr 24 23:10:48 2017 ROUX Hugues
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
			server/room.c \
			server/my_strncpy.c\
			server/my_strchr.c \
			server/commands.c \
			server/utils.c \
			server/off.c \
			server/my_strdup.c \
			server/fct_message_priver.c \
			server/create_client.c \
			server/bind_client.c \
			server/calback.c \
			server/create_room.c \
			server/my_strcpy.c \

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


ALL	:	lib server client

osx	:	lib_mac server client

server	:	$(SERVER_OBJ)
		$(CC) $(SERVER_OBJ) $(LIBS) -o $(SERVER_NAME) $(CFLAGS)

client	:	$(CLIENT_OBJ)
		$(CC) $(CLIENT_OBJ) $(LIBS) -o $(CLIENT_NAME) $(CFLAGS)

lib	:
		make -C libs/libmy

lib_mac	:
		make -C libs/libmy lib_mac

clean	:
		make -C libs/libmy clean
		$(RM) $(SERVER_OBJ)
		$(RM) $(CLIENT_OBJ)

fclean	:	clean
		make -C libs/libmy fclean
		$(RM) $(SERVER_NAME)
		$(RM) $(CLIENT_NAME)

re	:	fclean ALL

.PHONY	:	fclean

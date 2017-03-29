CC	=	gcc
NAME	=	multicopier
SRC	=	main.c \
		mcopy.c \
		mcopy_functions_1.c \
		mcopy_functions_2.c \
		copy.c	\
		string_utils.c
OBJ	=	$(SRC:%.c=%.o)
RM	=	rm -rf
LIBS	=	../libmy_extended.a
CFLAGS	=	-Wall -Wextra -Werror -g -lpthread

ALL	:	$(NAME) clean


$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME) $(CFLAGS)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean ALL

.PHONY	:	fclean

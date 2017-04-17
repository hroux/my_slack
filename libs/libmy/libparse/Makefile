CC	=	gcc
NAME	=	libparse
SRC	=	parser.c \
		parser_functions_1.c \
		arg_functions_1.c \
		option_functions_1.c \
		misc.c

OBJ	=	$(SRC:%.c=%.o)
RM	=	rm -f
LIBS	=	../liblist/liblist.a
DEPS	=	../liblist/liblist.so
CFLAGS	=	-Wall -Wextra -Werror -g -fPIC
SNAME   =       libparse.a
DNAME   =       libparse.so

ALL	:	$(NAME)

$(NAME) :	$(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME) $(CFLAGS)

clean	:
		$(RM) $(OBJ)

fclean  :	clean
		$(RM) $(NAME)

lib	:	$(OBJ)
		ar r $(SNAME) $(OBJ) $(LIBS)
		ranlib $(SNAME)
		$(CC) -o $(DNAME) $(OBJ) $(LIBS) -shared

lib_mac :	$(OBJ)
			libtool -static -o $(SNAME) $(OBJ)

re      :	fclean ALL

.PHONY	:	fclean

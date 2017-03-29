CC 	=	gcc
SRC	=	list.c \
		list_functions_1.c \
		list_functions_2.c

OBJ	=	$(SRC:%.c=%.o)
RM	=	rm -f
NAME	=	liblist
SNAME 	=	liblist.a
DNAME	=	liblist.so

CFLAGS 	= 	-W -Wall -Werror -fPIC -g

lib	:	$(OBJ)
		ar r $(SNAME) $(OBJ)
		ranlib $(SNAME)
		$(CC) -o $(DNAME) $(OBJ) -shared

lib_mac :	$(OBJ)
			libtool -static -o $(SNAME) $(OBJ)

.PHONY  :	fclean

ALL	:	$(NAME)

$(NAME) :	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean   :
		$(RM) $(OBJ)

fclean  :	clean
		$(RM) $(SNAME)
		$(RM) $(DNAME)

re      :	fclean ALL

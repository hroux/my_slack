CC	=	gcc
NAME	=	liblog
SRC	=	logger.c \
		loglevel.c \
		logconfig.c \
		logger_fn_1.c
OBJ	=	$(SRC:%.c=%.o)
RM	=	rm -rf
LIBS	=	../libprintf/libprintf.a
SNAME	=	liblog.a
DNAME	=	liblog.so
CFLAGS	=	-Wall -Wextra -Werror -g -fPIC

ALL	:	$(NAME) clean

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME) $(CFLAGS)

lib	:	$(OBJ)
		ar r $(SNAME) $(OBJ)
		ranlib $(SNAME)
		$(CC) -o $(DNAME) $(LIBS) $(OBJ) -shared

lib_mac :	$(OBJ)
			libtool -static -o $(SNAME) $(OBJ)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME) $(SNAME) $(DNAME)

re	:	fclean ALL

.PHONY	:	fclean

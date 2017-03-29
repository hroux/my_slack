CC 	= 	gcc

SRC 	= 	my_printf.c \
		functions.c \
		functions2.c \
		functions3.c \
		functions4.c \
		my_put_nbr.c \
		my_putchar.c \
		my_putstr.c \
		my_strlen.c \
		my_putnbr_base.c \
		my_putnbr_unsigned.c \
		my_putnbr_float.c

OBJ 	= 	$(SRC:%.c=%.o)

SNAME 	=	libprintf.a

DNAME	=	libprintf.so

CFLAGS 	= 	-W -Wall -Werror -fPIC -g

RM 	=	rm -f

my_printf :	$(OBJ)
		ar r $(SNAME) $(OBJ)
		ranlib $(SNAME)
		$(CC) -o $(DNAME) $(OBJ) -shared

lib_mac :	$(OBJ)
			libtool -static -o $(SNAME) $(OBJ)

lib	:	my_printf

clean :		
		$(RM) $(OBJ)

all :		my_printf

fclean :	clean
		$(RM) $(SNAME)
		$(RM) $(DNAME)

re :		fclean all

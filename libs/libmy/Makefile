CC	=	gcc
NAME	=	libmy_extended
RM	=	rm -rf
CFLAGS  =       -W -Wall -Werror -fPIC -g
SNAME   =       $(NAME).a
DNAME   =       $(NAME).so
SDEPS	=	libparse/libparse.a
DDEPS	=	libparse/libparse.so
LIBS    =   	liblist/liblist.a \
		libparse/libparse.a \
		libprintf/libprintf.a \
		liblog/liblog.a

ALL	:	$(NAME)

$(NAME)	:	
		make -C ./liblist/ lib
		make -C ./libparse/ lib
		make -C ./libprintf/ lib
		make -C ./liblog/ lib
		ar -M < $(NAME).mri
		ranlib $(SNAME)
		$(CC) -o $(DNAME) $(OBJ) $(DDEPS) -shared

lib_mac :
		make -C ./liblist/ lib_mac
		make -C ./libparse/ lib_mac
		make -C ./libprintf/ lib_mac
		make -C ./liblog/ lib_mac
		libtool -static -o $(SNAME) $(LIBS)

clean   :	
		$(RM) list_objs parse_objs
		make -C ./libparse/ clean
		make -C ./liblist/ clean
		make -C ./libprintf/ clean
		make -C ./liblog/ clean

fclean	:	clean
		$(RM) $(SNAME)
		$(RM) $(DNAME)
		make -C ./libparse/ fclean
		make -C ./liblist/ fclean
		make -C ./libprintf/ fclean
		make -C ./liblog/ fclean

re	:	fclean ALL

.PHONY	:	fclean

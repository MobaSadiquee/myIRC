##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Make serveur and client for irc
##

CC	= gcc

RM	= rm -rf

NAME1	= server

NAME2	= client

SRC1	=	src/server/basic_function.c \
		src/server/fd_manager.c \
		src/server/func_join.c \
		src/server/func_list.c \
		src/server/func_msg.c \
		src/server/func_nick.c \
		src/server/func_part.c \
		src/server/func_userbase.c \
		src/server/func_user.c \
		src/server/func_quit.c \
		src/server/func_ping.c \
		src/server/handle_connection.c \
		src/server/handle_socket.c \
		src/server/init_server.c \
		src/server/manage_connect.c \
		src/server/manage_arg.c \
		src/server/read_client.c \
		src/server/get_next_line.c \
		src/server/main.c

SRC2	=	src/client/client.c \
		src/client/connection.c \
		src/client/check_slash.c

OBJ1	= $(SRC1:.c=.o)

OBJ2	= $(SRC2:.c=.o)

CFLAGS	+= -I./include -I. -W -Wall -Wextra

LDFLAGS1 = -o $(NAME1)

LDFLAGS2 = -o $(NAME2)

all:	$(NAME1) $(NAME2)

$(NAME1):	$(OBJ1)
	$(CC) $(LDFLAGS1) $(OBJ1)

$(NAME2):	$(OBJ2)
	$(CC) $(LDFLAGS2) $(OBJ2)

server:		$(NAME1)

client:		$(NAME2)

clean:
	$(RM) $(OBJ1) $(OBJ2)

fclean: clean
	$(RM) $(NAME1) $(NAME2)

re:	fclean all

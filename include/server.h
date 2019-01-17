/*
** EPITECH PROJECT, 2018
** server.h
** File description:
** server header for irc project
*/

#ifndef SERVER_H_
# define SERVER_H_

#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <string.h>
#include <stdbool.h>
#include <netinet/in.h>

# define MAX_FD		255
# define MAX_CHAN	10

# define OK		0
# define KO		84

# define BUFF_MAX	512

typedef enum	s_usr_state
{
	OPEN = 1,
	CLOSE = 0,
}		t_usr_state;

typedef struct		s_usr
{
	t_usr_state		slot;
	int			fd;
	char			*pseudo;
	char			*old_name;
	char			*chan;
	char			*username;
	char			*name;
}			t_usr;

typedef struct		s_channel
{
	char		*name;
	t_usr		*users[10];
}			t_channel;

typedef struct		s_data
{
	int			fd;
	int			port;
	struct sockaddr_in	addr;
	fd_set			readfs;
	fd_set			writefs;
	t_usr			users[MAX_FD];
	t_channel		chan[MAX_CHAN];
}			t_data;

typedef struct		s_arg
{
	char		**av;
	char		*msg;
}			t_arg;

char	*get_next_line(const int fd);
void	free_argument(t_arg *, char *);
int	parse_argument(t_arg *, char *);
int	fd_manager(t_data *);
int	get_chan(t_data *, t_usr *, char *);
int	init_socket(void);
bool	bind_listen(t_data *, int, int);
int	init_server(t_data *);
bool	select_loop(t_data *);
bool	quit_server(t_usr *);
bool	manage_connect(t_data *);
void	my_error(char *);
int	read_client(t_data *, t_usr *);
bool	print_to_chan(t_data *, t_usr *, char *);

#endif  /* !SERVER_H_ */

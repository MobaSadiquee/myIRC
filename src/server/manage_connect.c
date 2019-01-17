/*
** EPITECH PROJECT, 2018
** get_connection
** File description:
** get connection for the server
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

static	t_usr	*get_user(t_data *serv, int client_fd)
{
	int	i = 0;

	while (i < MAX_FD)
	{
		if (serv->users[i].slot == OPEN)
			return ((t_usr *)&serv->users[i]);
		i = i + 1;
	}
	if (close(client_fd) == -1)
		my_error("[Error] Close.\n");
	my_error("[Status] Not enough slot for new user's ...\n");
	return (NULL);
}

bool	manage_connect(t_data *serv)
{
	int			client_fd;
	struct sockaddr_in	addr;
	socklen_t		size;
	t_usr			*user;

	size = sizeof(addr);
	client_fd = accept(serv->fd, (struct sockaddr *)&addr,
			&size);
	if (client_fd == -1)
	{
		my_error("[Error] Accept.\n");
		return (false);
	}
	user = get_user(serv, client_fd);
	if (user == NULL)
		return (false);
	user->fd = client_fd;
	user->slot = CLOSE;
	return (true);
}

/*
** EPITECH PROJECT, 2018
** fd_manager
** File description:
** manage client fd for server
*/

#include <stdio.h>
#include "server.h"

static	void	set_fd(t_data *serv)
{
	FD_ZERO(&serv->readfs);
	FD_SET(serv->fd, &serv->readfs);
	FD_ZERO(&serv->writefs);
}

static	int	loop_fd(t_data *serv)
{
	int	i = 0;
	int	res = serv->fd;

	while (i < MAX_FD)
	{
		if (serv->users[i].slot == CLOSE)
		{
			if (serv->users[i].fd > res)
				res = serv->users[i].fd;
			FD_SET(serv->users[i].fd, &serv->writefs);
			FD_SET(serv->users[i].fd, &serv->readfs);
		}
		i = i + 1;
	}
	return (res);
}

int	fd_manager(t_data *serv)
{
	int	res = 0;

	set_fd(serv);
	res = loop_fd(serv);
	return (res);
}

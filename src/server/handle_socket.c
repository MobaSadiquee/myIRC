/*
** EPITECH PROJECT, 2018
** handle_socket
** File description:
** handle socket for the server
*/

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

static	void	setopt(int fd)
{
	int	yes = 1;

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
			&yes, sizeof(yes)) == -1)
		my_error("[Error] setopt !");
}

bool	bind_listen(t_data *serv, int fd, int port)
{
	serv->addr.sin_family = AF_INET;
	serv->addr.sin_port = htons(port);
	serv->addr.sin_addr.s_addr = INADDR_ANY;
	setopt(fd);
	if (bind(fd, (const struct sockaddr *)&serv->addr,
		sizeof(serv->addr)) == -1)
	{
		my_error("[Error] bind !");
		return (false);
	}
	if (listen(fd, 100) == -1)
	{
		perror("[Error] listen !");
		return (false);
	}
	return (true);
}

int	init_socket(void)
{
	struct protoent		*proto;
	int			fd = 0;

	proto = getprotobyname("TCP");
	if (proto == NULL)
	{
		my_error("[Error] getprotobyname !");
		return (KO);
	}
	fd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	if (fd == -1)
	{
		my_error("[Error] socket !");
		return (KO);
	}
	return (fd);
}

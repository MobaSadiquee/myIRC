/*
** EPITECH PROJECT, 2018
** init_data
** File description:
** init server function
*/

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static t_data *server = NULL;

static	void	sig_handler(int sig)
{
	int   i = 0;

	(void)sig;
	printf("signal receved !\n");
	if (server == NULL)
		exit(OK);
	while (i < MAX_FD)
	{
		if (server->users[i].slot == CLOSE)
		{
			dprintf(server->users[i].fd,
				"Connection close by server.\r\n");
			close(server->users[i].fd);
		}
		i = i + 1;
	}
	exit(OK);
}

static	int	init_users(t_data *serv)
{
	int	i = 0;

	while (i < MAX_FD)
	{
		serv->users[i].slot = OPEN;
		serv->users[i].pseudo = NULL;
		serv->users[i].chan = NULL;
		serv->users[i].old_name = NULL;
		i = i + 1;
	}
	return (0);
}
static	int     init_channel(t_data *serv)
{
	int	i = 0;
	int	j;

	while (i < MAX_CHAN)
	{
		j = 0;
		while (j < MAX_CHAN)
		{
			serv->chan[i].users[j] = NULL;
			j = j + 1;
		}
		serv->chan[i].name = NULL;
		i += 1;
	}
	serv->chan[0].name = "#General";
	serv->chan[1].name = "#Gange";
	return (0);
}

int	init_server(t_data *serv)
{
	printf("[Status] Server is lunching...\n");
	init_users(serv);
	init_channel(serv);
	server = serv;
	signal(SIGINT, sig_handler);
	return (0);
}

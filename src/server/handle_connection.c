/*
** EPITECH PROJECT, 2018
** handle_connection
** File description:
** handle connection fort he server
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"

static	int     write_pause(t_data *serv, t_usr *usr)
{
	(void)serv;
	(void)usr;
	return (0);
}

static	bool	handle_users(t_data *serv)
{
	int	i = 0;

	if (FD_ISSET(serv->fd, &serv->readfs)) {
		if (manage_connect(serv) == false)
			printf("[Error] unable to manage new connection.\n");
		else
			printf("[Status] New user connected...\n");
	}
	while (i < MAX_FD) {
		if (serv->users[i].slot == CLOSE) {
			if (FD_ISSET(serv->users[i].fd, &serv->readfs))
				if ((read_client(serv,
						(t_usr*)&serv->users[i])) == KO)
					break ;
			if (FD_ISSET(serv->users[i].fd, &serv->writefs))
				write_pause(serv, (t_usr*)&serv->users[i]);
		}
		i = i + 1;
	}
	return (true);
}

bool	select_loop(t_data *serv)
{
	int	fd;
	int	sel = 0;

	while (1)
	{
		fd = fd_manager(serv);
		sel = select(fd + 1, &serv->readfs, &serv->writefs, NULL, NULL);
		if (sel == -1)
		{
			my_error("Select error !\n");
			return (false);
		}
		handle_users(serv);
	}
	return (true);
}

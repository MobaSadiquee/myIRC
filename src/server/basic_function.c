/*
** EPITECH PROJECT, 2018
** basic_function
** File description:
** basic function for the server
*/

#include "server.h"

static	bool	check_chan(t_data *serv, t_usr *usr, char *name)
{
	int	i = 0;

	while (i < MAX_CHAN)
	{
		if (serv->chan[i].name)
			if (strcmp(serv->chan[i].name, name) == 0)
				return (true);
		i = i + 1;
	}
	dprintf(usr->fd, "461 Channel %s don't exist !\r\n", name);
	return (false);
}

int	get_chan(t_data *serv, t_usr *user, char *name)
{
	int	i = 0;

	if (check_chan(serv, user, name) == false)
		return (KO);
	while (i < MAX_CHAN)
	{
		if (serv->chan[i].name)
			if (strcmp(serv->chan[i].name, name) == 0)
				return (i);
		i = i + 1;
	}
	return (KO);
}

void	my_error(char *str)
{
	int	i = 0;

	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
}

bool	quit_server(t_usr *user)
{
	if (close(user->fd) == -1)
	{
		perror("close()");
		return (false);
	}
	user->slot = OPEN;
	if (user->pseudo)
		free(user->pseudo);
	user->pseudo = NULL;
	return (true);
}

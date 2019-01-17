/*
** EPITECH PROJECT, 2018
** func_user
** File description:
** user function for server
*/

#include "server.h"

static	bool	list_names(t_data *serv, t_usr *user, char *name)
{
	int     i;
	int     j = 0;

	i = get_chan(serv, user, name);
	if (i == -1)
		return (false);
	while (j < MAX_CHAN)
	{
		if (serv->chan[i].users[j] != NULL)
			dprintf(user->fd, "335 :NAMES %s @ %s\r\n",
				serv->chan[i].users[j]->pseudo, name);
		j = j + 1;
	}
	return (false);
}

int	names_func(t_data *server, t_usr *user, t_arg *arg, int nb)
{
	printf("[Func] NAMES\n");
	if (nb < 2)
	{
		dprintf(user->fd, "461 NAMES : not enough param\r\n");
		return (KO);
	}
	if (list_names(server, user, arg->av[1]) == false)
		return (KO);
	return (0);
}

int     users_func(t_data *server, t_usr *user, t_arg *arg, int nb)
{
	int	i = 0;

	(void)arg;
	(void)nb;
	(void)user;
	printf("[Func] USERS\n");
	dprintf(user->fd, ":localhost 321 USERS\r\n");
	while (i < MAX_CHAN)
	{
		if (server->users[i].pseudo != NULL)
		{
			dprintf(user->fd, ":localhost 322 ");
			dprintf(user->fd, ":%s\r\n",
				server->users[i].pseudo);
		}
		i = i + 1;
	}
	dprintf(user->fd, ":localhost 323 DONE\r\n");
	return (0);
}

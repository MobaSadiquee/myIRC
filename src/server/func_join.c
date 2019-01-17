/*
** EPITECH PROJECT, 2018
** func_join
** File description:
** join function for the server
*/

#include "server.h"

static	int     join_chan(t_data *serv, t_usr *user, char *name)
{
	int     i = 0;

	(void)user;
	while (i < MAX_CHAN)
	{
		if (serv->chan[i].name)
			if (strcmp(serv->chan[i].name, name) == 0)
				return (i);
		i = i + 1;
	}
	return (KO);
}

static	int	get_new_chan(t_data *serv, char *s)
{
	int	i = 0;

	while (i < MAX_CHAN)
	{
		if (serv->chan[i].name == NULL)
		{
			serv->chan[i].name = strdup(s);
			return (i);
		}
		i = i + 1;
	}
	return (KO);
}

static	int	add_users(t_data *serv, t_usr *user, char *name)
{
	int	i;
	int	j = 0;

	i = join_chan(serv, user, name);
	if (i == KO)
		i = get_new_chan(serv, name);
	while (j < MAX_CHAN)
	{
		if (serv->chan[i].users[j] == NULL)
		{
			serv->chan[i].users[j] = user;
			user->chan = strdup(name);
			dprintf(user->fd, ":%s JOIN %s\r\n",
				user->pseudo, name);
			return (true);
		}
		j = j + 1;
	}
	return (false);
}

int	join_func(t_data *serv, t_usr *user, t_arg *arg, int nb)
{
	printf("[Func] JOIN\n");
	if (nb < 2)
	{
		dprintf(user->fd, "461 :not enough param\r\n");
		return (KO);
	}
	if (add_users(serv, user, arg->av[1]) == false)
		return (KO);
	return (0);
}

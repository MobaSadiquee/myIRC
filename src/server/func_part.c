/*
** EPITECH PROJECT, 2018
** func_part
** File description:
** part function for the server
*/

#include "server.h"

static	bool	remove_user(t_data *serv, t_usr *user, char *name)
{
	int	i;
	int	j = 0;

	i = get_chan(serv, user, name);
	if (i == KO)
		return (false);
	while (j < MAX_CHAN) {
		if (serv->chan[i].users[j] != NULL) {
			if (serv->chan[i].users[j]->fd == user->fd)
			{
				dprintf(user->fd, ":%s PART %s\r\n",
				user->pseudo, name);
				serv->chan[i].users[j] = NULL;
				user->chan = NULL;
				return (true);
			}
		}
		j = j + 1;
	}
	return (false);
}

int	part_func(t_data *serv, t_usr *user, t_arg *arg, int nb)
{
	if (nb < 2)
	{
		dprintf(user->fd, "461 PART :wrong param\r\n");
		return (KO);
	}
	if (remove_user(serv, user, arg->av[1]) == false)
	{
		dprintf(user->fd, "442 :User %s is not on this channel\r\n",
			user->pseudo);
		return (KO);
	}
	return (0);
}

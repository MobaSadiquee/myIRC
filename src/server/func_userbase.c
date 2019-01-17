/*
** EPITECH PROJECT, 2018
** func_userbase
** File description:
** userbase func for server
*/

#include "server.h"

static	void	register_user(t_usr *user, char *pseudo, char *name)
{
	user->username = strdup(pseudo);
	user->name = strdup(name);
}

int	userbase_func(t_data *serv, t_usr *user, t_arg *arg, int size)
{
	(void)serv;
	if (size < 5)
		return (dprintf(user->fd,
				":localhost 461 :Need more params.\r\n"), KO);
	if (user->name != NULL)
	{
		printf("pass\n");
		return (dprintf(user->fd,
				"462 :You are already registered.\r\n"), KO);
	}
	register_user(user, arg->av[1], arg->av[4]);
	dprintf(user->fd,
		":%s USER %s %s %s %s\r\n",
		user->pseudo,
		arg->av[1],
		arg->av[2],
		arg->av[3],
		arg->av[4]);
	dprintf(user->fd, ":localhost 001 %s :Welcome\r\n", user->pseudo);
	return (0);
}

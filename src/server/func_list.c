/*
** EPITECH PROJECT, 2018
** func_list
** File description:
** list function
*/

#include "server.h"

int	list_func(t_data *server, t_usr *user, t_arg *arg, int nb)
{
	int	i = 0;

	(void)arg;
	(void)nb;
	printf("[Func] LIST\n");
	dprintf(user->fd, ":localhost 321 %s LIST\r\n", user->pseudo);
	while (i < MAX_CHAN)
	{
		dprintf(user->fd, ":localhost 322 %s", user->pseudo);
		dprintf(user->fd, " %s\r\n", server->chan[i].name);
		i = i + 1;
	}
	dprintf(user->fd, ":localhost 323 %s :End of LIST\r\n", user->pseudo);
	return (0);
}

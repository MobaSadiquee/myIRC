/*
** EPITECH PROJECT, 2018
** func_privmsg
** File description:
** private message function for server
*/

#include "server.h"

bool	print_to_chan(t_data *serv, t_usr *user, char *msg)
{
	int	i;
	int	j = 0;

	i = get_chan(serv, user, user->chan);
	{
		while (j < MAX_CHAN)
		{
			if (serv->chan[i].users[j] != NULL &&
			serv->chan[i].users[j]->fd != user->fd)
			{
				dprintf(serv->chan[i].users[j]->fd,
					":localhost PRIVMSG %s :%s\r\n",
					serv->chan[i].name, msg);
			}
			j = j + 1;
		}
	}
	return (true);
}

bool	print_to_user(t_data *serv, t_usr *user, char *dest, char *msg)
{
	int	i = 0;

	while (i < MAX_FD)
	{
		if (serv->users[i].pseudo)
			if (strcasecmp(serv->users[i].pseudo, dest) == 0)
			{
				dprintf(serv->users[i].fd,
					":localhost PRIVMSG %s :%s\r\n",
					user->pseudo,
					msg);
				return (true);
			}
		i = i + 1;
	}
	return (false);
}

int	msg_func(t_data *serv, t_usr *user, t_arg *arg, int nb)
{
	printf("[Func] MSG\n");
	if (nb < 3)
	{
		dprintf(user->fd, "412 MSG :no text to send\r\n");
		return (KO);
	}
	if (print_to_user(serv, user, arg->av[1], arg->av[2]) == false)
	{
		dprintf(user->fd, "401 MSG :User don't exist !\r\n");
		return (KO);
	}
	return (0);
}

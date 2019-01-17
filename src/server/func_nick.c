/*
** EPITECH PROJECT, 2018
** func_nick
** File description:
** nick function for the server
*/

#include "server.h"

static	void	add_user(t_data *serv, t_usr *user, char *pseudo)
{
	int	i = 0;
	char	*name = pseudo;

	while (i < MAX_FD) {
		if (serv->users[i].slot == CLOSE) {
			if (serv->users[i].pseudo)
				if (strcmp(serv->users[i].pseudo, pseudo) == 0)
				{
					pseudo = malloc(sizeof(char)
							* (strlen(pseudo) + 2));
					pseudo = strcat(pseudo, name);
					pseudo = strcat(pseudo, "_");
				}
		}
		i = i + 1;
	}
	if (user->old_name != NULL)
		free(user->old_name);
	user->old_name = user->pseudo;
	user->pseudo = strdup(pseudo);
}

static	void	print_nick(t_usr *user)
{
	if (user->old_name != NULL)
		dprintf(user->fd, ":%s NICK %s\r\n",
			user->old_name, user->pseudo);
	else
		dprintf(user->fd, ":localhost NICK %s\r\n", user->pseudo);
	dprintf(user->fd, ":localhost 001 %s :Welcome\r\n", user->pseudo);
}

int	nick_func(t_data *serv, t_usr *user, t_arg *arg, int nb)
{
	printf("[Func] NICK\n");
	if (nb < 2)
	{
		dprintf(user->fd, ":localhost 461 :Need more argument.\r\n");
		return (KO);
	}
	if (arg->av[1] != NULL)
		add_user(serv, user, arg->av[1]);
	print_nick(user);
	return (0);
}

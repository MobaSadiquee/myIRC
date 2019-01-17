/*
** EPITECH PROJECT, 2018
** func_quit
** File description:
** quit function for the server
*/

#include "server.h"

int	quit_func(t_data *serv, t_usr *user, t_arg *arg, int nb)
{
	(void)serv;
	(void)nb;
	(void)arg;
	printf("[Func] QUIT\n");
	if (user->pseudo)
		dprintf(user->fd, "[%s] QUIT\r\n", user->pseudo);
	else
		dprintf(user->fd, "[Anonymous] QUIT\r\n");
	printf("[Status] User's left channel...\n");
	quit_server(user);
	return (OK);
}

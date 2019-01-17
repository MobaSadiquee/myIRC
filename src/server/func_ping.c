/*
** EPITECH PROJECT, 2018
** func_ping.c
** File description:
** ping function for server
*/

#include "server.h"

int     ping_func(t_data *serv, t_usr *user, t_arg *arg, int nb)
{
	(void)serv;
	(void)nb;
	dprintf(user->fd, "PONG %s\r\n", arg->av[0]);
	return (0);
}

/*
** EPITECH PROJECT, 2018
** func_read
** File description:
** read function for the server
*/

#include "server.h"
#include "function.h"

bool	do_function(t_data *serv, t_usr *user, t_arg *arg, int nb)
{
	int	i = 0;

	while (i < 10)
	{
		if (arg->av[0] == NULL)
			return (false);
		if (strcasecmp(function_name[i], arg->av[0]) == 0)
		{
			(function_ptr[i])(serv, user, arg, nb);
			return (true);
		}
		i = i + 1;
	}
	if (user->chan != NULL) {
		print_to_chan(serv, user, arg->msg);
		return (true);
	}
	else
		dprintf(user->fd, "%s: 421 unknown command\r\n", arg->av[0]);
	return (false);
}

int	read_client(t_data *serv, t_usr *user)
{
	t_arg	*arg = NULL;
	int	size = 0;
	char	*buff;

	arg = malloc(sizeof(t_arg));
	if (arg == NULL)
		return (KO);
	buff = get_next_line(user->fd);
	size = parse_argument(arg, buff);
	if (size == KO)
		return (KO);
	arg->msg = buff;
	do_function(serv, user, arg, size);
	free_argument(arg, buff);
	return (0);
}

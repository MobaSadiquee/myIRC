/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main function for the server
*/

#include "server.h"

static	int	check_port(char **av)
{
	int	port = 0;
	char	*check;

	port = strtol(av[1], &check, 10);
	if (check[0] != '\0')
	{
		printf("Server : Invalide port !\n");
		exit(KO);
	}
	return (port);
}

static	int	get_argument(int ac, char **av)
{
	int	port = 0;

	if (ac != 2)
	{
		printf("USAGE: ./server port\n");
		return (KO);
	}
	if (strcmp(av[1], "--help") == 0)
	{
		printf("USAGE: ./server port\n");
		return (KO);
	}
	port = check_port(av);
	return (port);
}

static	int	start_server(t_data serv)
{
	serv.fd = init_socket();
	if (serv.fd == KO)
		return (KO);
	if ((bind_listen(&serv, serv.fd, serv.port)) == false)
		return (KO);
	printf("[Status] Success. Waiting user's...\n");
	if (select_loop(&serv) == false)
		return (KO);
	return (OK);
}

int	main(int ac, char **av)
{
	t_data	serv;

	init_server(&serv);
	serv.port = get_argument(ac, av);
	if (serv.port == KO)
		return (KO);
	if ((start_server(serv)) == KO)
		return (KO);
	close(serv.fd);
	return (0);
}

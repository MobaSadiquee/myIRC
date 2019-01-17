/*
** EPITECH PROJECT, 2018
** client.c
** File description:
** client main function
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "client.h"

int	command_check(t_client *client, char *buf, size_t len)
{
	printf("$>");
	getline(&buf, &len, stdin);
	if (strcasecmp(buf, "quit\n") == 0)
		return (1);
	else if (strncasecmp(buf, "/server", 7) == 0)
		get_host(buf, client);
	else
		printf("error\n");
	return (0);
}

int	client_start(void)
{
	t_client	client;
	char		*buf = NULL;
	size_t		len = 0;
	int		value = 0;

	client.host = strdup("unknown");
	client.port = 8080;
	client.isconnected = DISCONNECTED;
	printf("welcome to my_irc\n"
	"to connect please use /server host[:port]\n");
	while (1) {
		value = command_check(&client, buf, len);
		if (value == 1)
			return (0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac > 1)
		return (84);
	if (client_start() == 84)
		return (84);
	return (0);
}

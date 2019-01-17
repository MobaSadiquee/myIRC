/*
** EPITECH PROJECT, 2018
** connection.c
** File description:
** connection header for client
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include "client.h"
#include "server.h"

int	do_select(t_client *client)
{
	int	fd = 0;

	FD_ZERO(&client->wfds);
	FD_ZERO(&client->rfds);
	FD_SET(STDIN_FILENO, &client->rfds);
	FD_SET(client->sock, &client->wfds);
	FD_SET(client->sock, &client->rfds);
	if (client->sock == -1)
		fd = STDERR_FILENO;
	else
		fd = client->sock;
	if (select(fd + 1, &client->rfds, &client->wfds, NULL, NULL) == -1)
		exit(84);
	return (0);
}

int	recup(int clientfd, char *command_sent, char *buffer)
{
	if (strcasecmp("quit", command_sent) == 0)
		exit(0);
	read(clientfd, buffer, 1024);
	printf("%s", buffer);
	return (0);
}

int	client_command(int clientfd, t_client *client)
{
	char	buffer[1024];
	char	*buf = NULL;
	char	*new_str;
	size_t	len = 0;

	memset(buffer, '\0', 1024);
	while (1) {
		do_select(client);
		if (FD_ISSET(STDIN_FILENO, &client->rfds)) {
			getline(&buf, &len, stdin);
			new_str = get_buffer(buf);
			write(clientfd, new_str, strlen(new_str));
			free(new_str);
		}
		else if (FD_ISSET(client->sock, &client->rfds)) {
			recup(clientfd, buf, buffer);
			memset(buffer, '\0', 1024);
		}
	}
	return (0);
}

int	client_connection(t_client *client)
{
	struct sockaddr_in	serv_addr;
	struct protoent		*pe;
	int			clientfd = 0;

	pe = getprotobyname("TCP");
	clientfd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(client->port);
	inet_pton(AF_INET, client->host, &serv_addr.sin_addr);
	if ((connect(clientfd, (struct sockaddr *)&serv_addr,
		sizeof(serv_addr))) == -1)
		exit(0);
	client->isconnected = CONNECTED;
	client->sock = clientfd;
	client_command(clientfd, client);
	return (0);
}

int	get_host(char *command, t_client *client)
{
	char	*adress = NULL;
	char	*port_ = NULL;
	int	i = 0;

	adress = strtok(command, " ");
	adress = strtok(NULL, " ");
	if (!adress)
		return (0);
	adress = strtok(adress, ":");
	port_ = strtok(NULL, ":");
	if (port_ == NULL || adress == NULL)
		return (0);
	if (port_)
		client->port = atoi(port_);
	while (adress[i + 1] != '\n')
		i++;
	adress[i + 1] = '\0';
	client->host = adress;
	client_connection(client);
	return (0);
}

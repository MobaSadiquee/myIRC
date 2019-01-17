/*
** EPITECH PROJECT, 2018
** client.h
** File description:
** header for the client
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include "server.h"

typedef enum 	t_etat {
	CONNECTED,
	DISCONNECTED,
	UNKNOWN
}		e_etat;

typedef struct	s_client {
	char *host;
	int port;
	e_etat isconnected;
	int	sock;
	fd_set	rfds;
	fd_set	wfds;
}		t_client;

int	get_host(char *command, t_client *client);
char	*get_buffer(char *str);

#endif /*CLIENT_H_*/

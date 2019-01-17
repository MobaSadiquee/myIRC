/*
** EPITECH PROJECT, 2018
** selector.h
** File description:
** selector header for the server
*/

#ifndef SELECTOR_H_
# define SELECTOR_H_

#include "server.h"

char	*function_name[] = {
	"nick",
	"join",
	"quit",
	"part",
	"msg",
	"list",
	"names",
	"users",
	"user",
	"ping",
	NULL
};

int	nick_func(t_data *, t_usr *, t_arg *, int);
int	join_func(t_data *, t_usr *, t_arg *, int);
int	quit_func(t_data *, t_usr *, t_arg *, int);
int	part_func(t_data *, t_usr *, t_arg *, int);
int	msg_func(t_data *, t_usr *, t_arg *, int);
int	list_func(t_data *, t_usr *, t_arg *, int);
int	names_func(t_data *, t_usr *, t_arg *, int);
int	users_func(t_data *, t_usr *, t_arg *, int);
int     userbase_func(t_data *, t_usr *, t_arg *, int);
int     ping_func(t_data *, t_usr *, t_arg *, int);

int	(*function_ptr[])(t_data *, t_usr *, t_arg *, int) = {
	nick_func,
	join_func,
	quit_func,
	part_func,
	msg_func,
	list_func,
	names_func,
	users_func,
	userbase_func,
	ping_func,
};

#endif /* !SELECTOR_H_ */

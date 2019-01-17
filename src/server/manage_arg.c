/*
** EPITECH PROJECT, 2018
** querry_module
** File description:
** querry module
*/

#include "server.h"

static	char	**malloc_av(char **str, int size)
{
	char	**new;
	int	i = 0;

	new = malloc(sizeof(char *) * (size + 1));
	if (new == NULL)
		return (NULL);
	new[size] = NULL;
	if (str == NULL)
		return (new);
	while (str[i] != NULL)
	{
		new[i] = str[i];
		i += 1;
	}
	if (str != NULL)
		free(str);
	return (new);
}

int	parse_argument(t_arg *arg, char *buff)
{
	int	size = 0;
	char	*tmp;

	if (buff == NULL)
		return (KO);
	if (buff[0] == '\n')
		return (KO);
	arg->av = malloc_av(NULL, size);
	if (arg->av == NULL)
		return (KO);
	tmp = strtok(buff, " \n\r");
	while (tmp != NULL) {
		size = size + 1;
		arg->av = malloc_av(arg->av, size);
		if (arg->av == NULL)
			return (KO);
		arg->av[size - 1] = tmp;
		tmp = strtok(NULL, " \n\r");
	}
	return (size);
}

void    free_argument(t_arg *arg, char * buff)
{
	if (arg->av)
		free(arg->av);
	if (buff != NULL)
		free(buff);
}

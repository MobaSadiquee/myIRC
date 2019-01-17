/*
** EPITECH PROJECT, 2018
** check_slash.c
** File description:
** get slash and remove it
*/

#include "client.h"

char	*get_buffer(char *str)
{
	int	i = 0;
	int	j = 0;
	char	*new_str;

	new_str = malloc(sizeof(char) * 1024);
	if (new_str == NULL)
		exit(0);
	if (str[i] == '/')
		i++;
	while (str[i] != '\0') {
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

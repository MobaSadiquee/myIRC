/*
** EPITECH PROJECT, 2018
** getnextline
** File description:
** getline
*/

#include "server.h"

static	char    *my_realloc(char *str)
{
	char	*new_str;
	int	i = 0;

	new_str = malloc((strlen(str) + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static	char	get_fd(const int fd, int option)
{
	static char	buffer[BUFF_MAX];
	static char	*str = NULL;
	char		word;
	static int	readed = 0;

	(void)option;
	if (readed == 0)
	{
		if ((readed = read(fd, buffer, BUFF_MAX)) < 0)
			return (0);
		str = buffer;
		if (readed < 1)
			return (0);
	}
	word = *str;
	str++;
	readed--;
	return (word);
}

static	char	*loop_line(char *str, char word, int fd, int option)
{
	int	i = 0;

	while (word != '\n' && word != '\0')
	{
		option++;
		str[i] = word;
		word = get_fd(fd, option);
		if (word == 0)
			return (NULL);
		i++;
		if (i % (BUFF_MAX + 1) == 0)
		{
			str = my_realloc(str);
			if (str == NULL)
				return (NULL);
		}
	}
	str[i] = '\0';
	return (str);
}

char    *get_next_line(const int fd)
{
	char	word;
	char	*str;
	static int	option = 0;

	str = malloc(sizeof(char) * BUFF_MAX + 1);
	if (str == NULL)
		return (NULL);
	word = get_fd(fd, option);
	if (word == 0)
		return (NULL);
	str = loop_line(str, word, fd, option);
	if (str == NULL)
		return (NULL);
	if (str[0] == 0)
		return (NULL);
	return (str);
}

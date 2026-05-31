#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gnl.h>
#include <stdio.h>
#include <dict.h>
#include "libftutils.h"

int test_for_textures(t_dict *dict)
{
	if (!dict_get(dict, "NO"))
		return (0);
	if (!dict_get(dict, "SO"))
		return (0);
	if (!dict_get(dict, "WE"))
		return (0);
	if (!dict_get(dict, "EA"))
		return (0);
	if (!dict_get(dict, "F"))
		return (0);
	if (!dict_get(dict, "C"))
		return (0);
	return (1);
}

t_dict	*map_load(char *path)
{
	int fd;
	char *str;
	t_dict *dict;
	char *token;

	dict = calloc(1, sizeof(dict));
	char *temp;
	temp = NULL;
	str = NULL;
	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		token = ft_strtok(str, ' ');
		if (token)
		{
			temp = token;
			token = ft_strtok(NULL, ' ');
			if (token)
			{
				if (dict_set(&dict, temp, token) == -1)
					return (NULL);
			}
		}
		str = get_next_line(fd);
	}
	return (dict);
}

void	map_display(char **map, int x, int y)
{
	int	i;
	int	j;

	(void)map;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			j++;
		}
		i++;
	}
}

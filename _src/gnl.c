#include <stdio.h>

#include "dict.h"
#include "minilibft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gnl.h>

#define BUFFER_SIZE 10


int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1;

	if (*s1 == NULL)
	{
		(*s1) = malloc(1);
		(*s1)[0] = 0;
	}
	size1 = strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	memcpy(tmp, *s1, size1);
	memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, strlen(s2)));
}

char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = strchr(b, '\n');
	while (!((tmp = strchr(b, '\n'))))
	{
		if (!str_append_str(&ret, b))
			return (NULL);
		int read_ret = read(fd, b, BUFFER_SIZE);

		if (read_ret == -1)
		{
			b[0] = 0;
			free(ret);
			return (NULL);
		}

		if (read_ret == 0)
		{
			b[0] = 0;
			if (ret && ret[0])
				return (ret);
			free(ret);
			return (NULL);
		}
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
	memmove(b, tmp + 1, strlen(tmp + 1) + 1);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:57:48 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 22:27:18 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"
#include "libftutils.h"
#include <fcntl.h>
#include <gnl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	if (*s1 == NULL)
	{
		(*s1) = malloc(1);
		(*s1)[0] = 0;
	}
	size1 = ft_strlen(*s1);
	tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, strlen(s2)));
}

static char	*read_until_newline(int fd, char *b, char **ret)
{
	int	read_ret;

	while (!ft_strchr(b, '\n'))
	{
		if (!str_append_str(ret, b))
			return (NULL);
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
			b[0] = 0;
			free(*ret);
			*ret = NULL;
			return (NULL);
		}
		if (read_ret == 0)
		{
			b[0] = 0;
			if (*ret && (*ret)[0])
				return (*ret);
			free(*ret);
			return (NULL);
		}
		b[read_ret] = 0;
	}
	return ((char *)1);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char		*ret;
	char		*tmp;
	char		*loop_ret;

	ret = NULL;
	loop_ret = read_until_newline(fd, b, &ret);
	if (loop_ret == NULL)
		return (NULL);
	if (loop_ret != (char *)1)
		return (loop_ret);
	tmp = ft_strchr(b, '\n');
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
	ft_memmove(b, tmp + 1, strlen(tmp + 1) + 1);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:12:44 by jde-carv          #+#    #+#             */
/*   Updated: 2026/06/10 18:15:29 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_tex_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strcmp(path + len - 4, ".xpm") == 0)
		return (1);
	if (ft_strcmp(path + len - 4, ".png") == 0)
		return (1);
	return (0);
}

int	validate_tex_path(char *path)
{
	int	fd;

	if (!check_tex_extension(path))
		return (parse_error(E_TEX_FMT), -1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (parse_error(E_TEX_FILE), -1);
	close(fd);
	return (0);
}

char	*extract_path(char *line)
{
	char	*start;
	char	*end;
	int		len;
	char	*path;

	start = line + 3;
	while (*start == ' ')
		start++;
	if (!*start || *start == '\n')
		return (NULL);
	end = start;
	while (*end && *end != ' ' && *end != '\n')
		end++;
	while (*end == ' ')
	{
		if (*(end + 1) && *(end + 1) != ' ' && *(end + 1) != '\n')
			return (NULL);
		end++;
	}
	len = 0;
	while (start[len] && start[len] != ' ' && start[len] != '\n')
		len++;
	path = ft_substr(start, 0, len);
	return (path);
}

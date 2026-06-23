/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:12:44 by jde-carv          #+#    #+#             */
/*   Updated: 2026/06/23 19:05:08 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_file_ext(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strcmp(path + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

static int	process_line(char *line, t_parse_data *data, int *map_started)
{
	int	ret;

	if (has_tab(line))
	{
		free(line);
		return (parse_error(E_TAB), -1);
	}
	ret = parse_line(line, data, map_started);
	free(line);
	return (ret);
}

static int	read_file_lines(int fd, t_parse_data *data)
{
	char	*line;
	int		map_started;
	int		got_content;

	map_started = 0;
	got_content = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		got_content = 1;
		if (process_line(line, data, &map_started) == -1)
			return (-1);
		line = get_next_line(fd);
	}
	if (!got_content)
		return (parse_error(E_EMPTY), -1);
	return (0);
}

static int	validate_final(t_parse_data *data)
{
	if (!has_all_elements(data))
		return (parse_error(E_TEX_MISS), -1);
	if (!data->map || data->map_h == 0)
		return (parse_error(E_MAP_MISS), -1);
	if (validate_map(data) == -1)
		return (-1);
	data->flags.has_map = 1;
	data->flags.walls_closed = 1;
	return (0);
}

int	parse_file(char *path, t_parse_data *data)
{
	int	fd;

	init_parse_data(data);
	if (!check_file_ext(path))
		return (parse_error(E_EXT), -1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (parse_error(E_OPEN), -1);
	data->flags.file_valid = 1;
	if (read_file_lines(fd, data) == -1)
	{
		close(fd);
		free_parse_data(data);
		return (-1);
	}
	close(fd);
	if (validate_final(data) == -1)
		return (free_parse_data(data), -1);
	if (!flags_all_set(&data->flags))
		return (parse_error(E_TEX_MISS), free_parse_data(data), -1);
	return (0);
}

/*
int	parse_file(char *path, t_parse_data *data)
{
	int	fd;

	init_parse_data(data);
	if (!check_file_ext(path))
		return (parse_error(E_EXT), -1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (parse_error(E_OPEN), -1);
	data->flags.file_valid = 1;
	if (read_file_lines(fd, data) == -1)
	{
		close(fd);
		free_parse_data(data);
		return (-1);
	}
	close(fd);
	if (validate_final(data) == -1)
		return (free_parse_data(data), -1);
	if (!flags_all_set(&data->flags))
		return (parse_error(E_TEX_MISS), free_parse_data(data), -1);
	return (0);
}
*/
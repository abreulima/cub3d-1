/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:12:44 by jde-carv          #+#    #+#             */
/*   Updated: 2026/06/23 18:58:48 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	get_map_char(t_parse_data *data, int x, int y)
{
	int	len;

	if (y < 0 || y >= data->map_h)
		return (' ');
	len = ft_strlen(data->map[y]);
	if (x < 0 || x >= len)
		return (' ');
	return (data->map[y][x]);
}

static int	check_space_neighbors(t_parse_data *data, int x, int y)
{
	char	c;

	c = get_map_char(data, x - 1, y);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	c = get_map_char(data, x + 1, y);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	c = get_map_char(data, x, y - 1);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	c = get_map_char(data, x, y + 1);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

static int	check_border_cell(t_parse_data *data, int x, int y)
{
	char	c;

	c = get_map_char(data, x, y);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (x == 0 || y == 0 || y == data->map_h - 1)
			return (0);
		if (x >= (int)ft_strlen(data->map[y]) - 1)
			return (0);
		if (get_map_char(data, x - 1, y) == ' ')
			return (0);
		if (get_map_char(data, x + 1, y) == ' ')
			return (0);
		if (get_map_char(data, x, y - 1) == ' ')
			return (0);
		if (get_map_char(data, x, y + 1) == ' ')
			return (0);
	}
	return (1);
}

static int	check_walls_row(t_parse_data *data, int y)
{
	int	x;
	int	len;

	len = ft_strlen(data->map[y]);
	x = 0;
	while (x < len)
	{
		if (!check_border_cell(data, x, y))
			return (0);
		if (data->map[y][x] == ' ')
		{
			if (!check_space_neighbors(data, x, y))
				return (0);
		}
		x++;
	}
	return (1);
}

int	validate_map(t_parse_data *data)
{
	int	y;
	int	only_spaces;

	if (data->player_dir == 0)
		return (parse_error(E_MAP_PLAYER), -1);
	data->flags.has_player = 1;
	only_spaces = 1;
	y = 0;
	while (y < data->map_h)
	{
		if (!is_empty_line(data->map[y]))
			only_spaces = 0;
		if (!check_walls_row(data, y))
			return (parse_error(E_MAP_WALL), -1);
		y++;
	}
	if (only_spaces)
		return (parse_error(E_MAP_MISS), -1);
	return (0);
}

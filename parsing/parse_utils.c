/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:12:44 by jde-carv          #+#    #+#             */
/*   Updated: 2026/06/10 18:09:52 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_tab(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*skip_spaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	init_parse_data(t_parse_data *data)
{
	ft_bzero(data, sizeof(t_parse_data));
	data->floor_r = -1;
	data->floor_g = -1;
	data->floor_b = -1;
	data->ceil_r = -1;
	data->ceil_g = -1;
	data->ceil_b = -1;
	data->player_x = -1;
	data->player_y = -1;
}

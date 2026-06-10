/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:12:44 by jde-carv          #+#    #+#             */
/*   Updated: 2026/06/09 20:42:12 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_single_value(char **str, int *val)
{
	char	*start;
	char	*end;
	char	tmp;

	start = *str;
	while (*start == ' ')
		start++;
	if (!*start || *start == ',' || *start == '\n')
		return (0);
	end = start;
	while (*end && *end != ',' && *end != '\n')
		end++;
	tmp = *end;
	*end = '\0';
	if (!ft_atoi_safe(start, val))
	{
		*end = tmp;
		return (0);
	}
	*end = tmp;
	*str = end;
	return (1);
}

static int	parse_rgb_values(char *str, int *r, int *g, int *b)
{
	if (!parse_single_value(&str, r))
		return (0);
	if (*str != ',')
		return (0);
	str++;
	if (!parse_single_value(&str, g))
		return (0);
	if (*str != ',')
		return (0);
	str++;
	if (!parse_single_value(&str, b))
		return (0);
	while (*str == ' ')
		str++;
	if (*str && *str != '\n')
		return (0);
	return (1);
}

static int	assign_floor(char *str, t_parse_data *data)
{
	if (data->flags.has_color_floor)
		return (parse_error(E_CLR_DUP), -1);
	if (!parse_rgb_values(str, &data->floor_r, &data->floor_g, &data->floor_b))
		return (parse_error(E_CLR_FMT), -1);
	data->flags.has_color_floor = 1;
	return (0);
}

static int	assign_ceil(char *str, t_parse_data *data)
{
	if (data->flags.has_color_ceil)
		return (parse_error(E_CLR_DUP), -1);
	if (!parse_rgb_values(str, &data->ceil_r, &data->ceil_g, &data->ceil_b))
		return (parse_error(E_CLR_FMT), -1);
	data->flags.has_color_ceil = 1;
	return (0);
}

int	parse_color(char *line, t_parse_data *data)
{
	char	*str;

	if (line[0] == 'F')
		str = line + 2;
	else
		str = line + 2;
	if (!*str || *str == '\n')
		return (parse_error(E_CLR_FMT), -1);
	if (line[0] == 'F')
		return (assign_floor(str, data));
	return (assign_ceil(str, data));
}

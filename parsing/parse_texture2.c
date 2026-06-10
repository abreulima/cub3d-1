/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:12:44 by jde-carv          #+#    #+#             */
/*   Updated: 2026/06/10 18:19:50 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	assign_texture(char *path, char **dest)
{
	if (*dest != NULL)
		return (free(path), parse_error(E_TEX_DUP), -1);
	if (validate_tex_path(path) == -1)
		return (free(path), -1);
	*dest = path;
	return (0);
}

int	parse_tex_dir(char *line, char *path, t_parse_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (assign_texture(path, &data->tex_no) == -1)
			return (-1);
		return (data->flags.has_tex_no = 1, 0);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (assign_texture(path, &data->tex_so) == -1)
			return (-1);
		return (data->flags.has_tex_so = 1, 0);
	}
	return (2);
}

int	parse_texture(char *line, t_parse_data *data)
{
	char	*path;
	int		ret;

	path = extract_path(line);
	if (!path)
		return (parse_error(E_TEX_FMT), -1);
	ret = parse_tex_dir(line, path, data);
	if (ret <= 0)
		return (ret);
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (assign_texture(path, &data->tex_we) == -1)
			return (-1);
		return (data->flags.has_tex_we = 1, 0);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (assign_texture(path, &data->tex_ea) == -1)
			return (-1);
		return (data->flags.has_tex_ea = 1, 0);
	}
	return (free(path), parse_error(E_TEX_FMT), -1);
}

#include "parsing.h"

int	ft_atoi_safe(char *str, int *result)
{
	long	num;

	num = 0;
	if (!*str)
		return (0);
	while (*str == ' ')
		str++;
	if (!*str)
		return (0);
	while (*str && *str != ' ')
	{
		if (!ft_isdigit(*str))
			return (0);
		num = num * 10 + (*str - '0');
		if (num > 255)
			return (0);
		str++;
	}
	while (*str == ' ')
		str++;
	if (*str && *str != '\0')
		return (0);
	*result = (int)num;
	return (1);
}

int	has_all_elements(t_parse_data *data)
{
	if (!data->flags.has_tex_no || !data->flags.has_tex_so)
		return (0);
	if (!data->flags.has_tex_we || !data->flags.has_tex_ea)
		return (0);
	if (!data->flags.has_color_floor || !data->flags.has_color_ceil)
		return (0);
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (i > 0);
}

void	free_parse_data(t_parse_data *data)
{
	int	i;

	if (data->tex_no)
		free(data->tex_no);
	if (data->tex_so)
		free(data->tex_so);
	if (data->tex_we)
		free(data->tex_we);
	if (data->tex_ea)
		free(data->tex_ea);
	if (data->map)
	{
		i = 0;
		while (i < data->map_h)
			free(data->map[i++]);
		free(data->map);
	}
}

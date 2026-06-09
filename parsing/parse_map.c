#include "parsing.h"

static int	get_line_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

static int	check_map_chars(char *line, t_parse_data *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			if (data->player_dir != 0)
				return (parse_error(E_MAP_PLAYER), -1);
			data->player_dir = line[i];
			data->player_x = i;
			data->player_y = data->map_h;
		}
		else if (line[i] != '0' && line[i] != '1' && line[i] != ' ')
			return (parse_error(E_MAP_CHAR), -1);
		i++;
	}
	return (0);
}

static char	*copy_map_line(char *line, int len, int width)
{
	char	*row;
	int		i;

	row = malloc(width + 1);
	if (!row)
		return (NULL);
	i = 0;
	while (i < width)
	{
		if (i < len)
			row[i] = line[i];
		else
			row[i] = ' ';
		i++;
	}
	row[i] = '\0';
	return (row);
}

static int	add_map_row(t_parse_data *data, char *row)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (data->map_h + 1));
	if (!new_map)
		return (free(row), parse_error(E_MALLOC), -1);
	i = 0;
	while (i < data->map_h)
	{
		new_map[i] = data->map[i];
		i++;
	}
	new_map[i] = row;
	if (data->map)
		free(data->map);
	data->map = new_map;
	data->map_h++;
	return (0);
}

int	parse_map_line(char *line, t_parse_data *data)
{
	int		len;
	char	*row;

	if (check_map_chars(line, data) == -1)
		return (-1);
	len = get_line_len(line);
	if (len > data->map_w)
		data->map_w = len;
	row = copy_map_line(line, len, data->map_w);
	if (!row)
		return (parse_error(E_MALLOC), -1);
	return (add_map_row(data, row));
}

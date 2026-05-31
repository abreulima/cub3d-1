#include "parsing.h"

static int	is_texture_id(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

static int	is_color_id(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static int	handle_map_line(char *line, t_parse_data *data, int *map_started)
{
	if (!has_all_elements(data))
		return (parse_error(E_TEX_MISS), -1);
	*map_started = 1;
	return (parse_map_line(line, data));
}

int	parse_line(char *line, t_parse_data *data, int *map_started)
{
	if (is_empty_line(line))
	{
		if (*map_started && data->map_h > 0)
			*map_started = 2;
		return (0);
	}
	if (*map_started == 2)
		return (parse_error(E_MAP_ORDER), -1);
	if (*map_started == 1 && !is_map_line(line))
		return (parse_error(E_MAP_ORDER), -1);
	if (!*map_started && is_texture_id(line))
		return (parse_texture(line, data));
	if (!*map_started && is_color_id(line))
		return (parse_color(line, data));
	if (is_map_line(line))
		return (handle_map_line(line, data, map_started));
	return (parse_error(E_ELEM), -1);
}

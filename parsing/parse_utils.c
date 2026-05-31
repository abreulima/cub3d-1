#include "parsing.h"

static const char	*g_err_msgs[E_COUNT] = {
	"Error\nUsage: ./cub3d <map.cub>\n",
	"Error\nFile must have .cub extension\n",
	"Error\nCannot open file\n",
	"Error\nFile is empty\n",
	"Error\nInvalid texture format\n",
	"Error\nCannot open texture file\n",
	"Error\nDuplicate texture definition\n",
	"Error\nMissing texture definition\n",
	"Error\nInvalid color format\n",
	"Error\nDuplicate color definition\n",
	"Error\nInvalid character in map\n",
	"Error\nMap must have exactly one player\n",
	"Error\nMap is not surrounded by walls\n",
	"Error\nNo map found in file\n",
	"Error\nMap must be last element in file\n",
	"Error\nTabs are not allowed\n",
	"Error\nInvalid element in file\n",
	"Error\nMemory allocation failed\n",
	"Error\nUnable to init MLX\n"
};

int	flags_all_set(t_flags *f)
{
	if (!f->file_valid || !f->has_tex_no)
		return (0);
	if (!f->has_tex_so || !f->has_tex_we)
		return (0);
	if (!f->has_tex_ea || !f->has_color_floor)
		return (0);
	if (!f->has_color_ceil || !f->has_map)
		return (0);
	if (!f->has_player || !f->walls_closed)
		return (0);
	return (1);
}

void	parse_error(int err_id)
{
	if (err_id >= 0 && err_id < E_COUNT)
		ft_putstr((char *)g_err_msgs[err_id]);
}

char	*get_err_msg(int err_id)
{
	if (err_id >= 0 && err_id < E_COUNT)
		return ((char *)g_err_msgs[err_id]);
	return (NULL);
}

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

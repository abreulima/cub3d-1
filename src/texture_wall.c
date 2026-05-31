#include "cub3d.h"
#include "libftutils.h"
#include <stdio.h>

int	load_texture(t_game *g, t_dict *dict)
{
	char				*loading;
	int i;
	static const char	dir[4][3] = {"NO", "WE", "EA", "SO"};

	i = 0;
	while (i < 4)
	{
		loading = ft_strtrim(dict_get(dict, dir[i]), " \t\n\v\f\r");
		ft_putstr("Loading...\t");
		ft_putstr(loading);
		(void)!write(1, "\n", 1);
		g->map.walls[i] = image_loader(g, loading);
		if (g->map.walls[i].ptr == NULL)
		{
			free(loading);
			return (-1);
		}
		free(loading);
		i++;	
	}
	return (1);
}

int	*get_buffer_wall(t_game *g, int ray_id)
{
	t_ray	ray;

	ray = g->rays[ray_id];
	if (ray.is_vertical_hit)
	{
		if (ray.is_facing_right)
			return (g->map.walls[NORTH].buffer);
		else
			return (g->map.walls[WEST].buffer);
	}
	else
	{
		if (ray.is_facing_up)
			return (g->map.walls[NORTH].buffer);
		else
			return (g->map.walls[SOUTH].buffer);
	}
}

int	get_texture_color(t_game *g, int ray_id, int y, int height)
{
	int		color;
	int		texture_offset_y;
	int		texture_offset_x;
	int		*buffer;
	int		distance_from_top;
	float	normalize_dist;

	distance_from_top = y + (height / 2) - (WINDOW_HEIGHT / 2);
	if (g->rays[ray_id].is_vertical_hit)
		texture_offset_x = (int)g->rays[ray_id].wall_hit_y % TILE_SIZE;
	else
		texture_offset_x = (int)g->rays[ray_id].wall_hit_x % TILE_SIZE;
	texture_offset_y = distance_from_top * ((float)TILE_SIZE / height);
	normalize_dist = 1.0 - g->rays[ray_id].distance / (WINDOW_WIDTH * 0.8);
	buffer = get_buffer_wall(g, ray_id);
	color = buffer[(TILE_SIZE * texture_offset_y) + texture_offset_x];
	return (blend(color, 0, normalize_dist));
}

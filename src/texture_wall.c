/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:58:13 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 16:37:20 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libftutils.h"

int	load_texture(t_game *g, t_dict *dict)
{
	char				*loading;
	int					i;
	static const char	dir[4][3] = {"NO", "WE", "EA", "SO"};

	i = 0;
	while (i < 4)
	{
		loading = ft_strtrim(dict_get(dict, dir[i]), " \t\n\v\f\r");
		(void)!write(1, "\n", 1);
		g->map.walls[i] = image_loader(g, loading);
		if (g->map.walls[i].ptr == NULL)
		{
			free(loading);
			return (-1);
		}
		g->map.walls[i].buffer = (int *)mlx_get_data_addr(
				g->map.walls[i].ptr,
				&g->map.walls[i].bits_per_pixel,
				&g->map.walls[i].line_length,
				&g->map.walls[i].endian);
		g->map.walls[i].line_length /= 4;
		free(loading);
		i++;
	}
	return (1);
}

static int	*get_buffer_wall(t_game *g, int ray_id)
{
	t_ray	ray;

	ray = g->rays[ray_id];
	if (ray.is_vertical_hit)
	{
		if (ray.is_facing_right)
			return (g->map.walls[EAST].buffer);
		return (g->map.walls[WEST].buffer);
	}
	if (ray.is_facing_up)
		return (g->map.walls[NORTH].buffer);
	return (g->map.walls[SOUTH].buffer);
}

unsigned int	blend(int main, int accent, float pct)
{
	int	red;
	int	green;
	int	blue;

	(void)accent;
	if (pct < .2)
		pct = .2;
	red = ((main & 0xFF0000) >> 16) * pct;
	green = ((main & 0x00FF00) >> 8) * pct;
	blue = ((main & 0x0000FF) >> 0) * pct;
	return ((0x00 << 24) | (red << 16) | (green << 8) | (blue));
}

int	get_texture_color(t_game *g, int ray_id, int y, int height)
{
	int		color;
	int		texture_offset_y;
	int		texture_offset_x;
	int		*buffer;
	float	normalize_dist;

	if (g->rays[ray_id].is_vertical_hit)
		texture_offset_x = (int)g->rays[ray_id].wall_hit_y % TILE_SIZE;
	else
		texture_offset_x = (int)g->rays[ray_id].wall_hit_x % TILE_SIZE;
	texture_offset_y = (int)((float)(y - (WINDOW_HEIGHT / 2 - height / 2))
			/ height * TILE_SIZE);
	if (texture_offset_y < 0)
		texture_offset_y = 0;
	if (texture_offset_y >= TILE_SIZE)
		texture_offset_y = TILE_SIZE - 1;
	normalize_dist = 1.0 - g->rays[ray_id].distance / (WINDOW_WIDTH * 0.8);
	buffer = get_buffer_wall(g, ray_id);
	if (!buffer)
		return (0xFF00FF);
	color = buffer[(TILE_SIZE * texture_offset_y) + texture_offset_x];
	return (blend(color, 0, normalize_dist));
}

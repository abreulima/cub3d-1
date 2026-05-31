#include "cub3d.h"
#include <math.h>
#include <stdio.h>

// Source - https://stackoverflow.com/a/12016968
// Posted by Sniggerfardimungus
// Retrieved 2026-03-10, License - CC BY-SA 3.0

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
	return (0x00 << 24) | (red << 16) | (green << 8) | (blue);
}

int	get_color_from_texture(t_game *g, int ray_id)
{
	t_ray	ray;
	float	normalize_dist;

	// printf("%f\n", normalize(g->rays[ray_id].distance, WINDOW_WIDTH) );
	ray = g->rays[ray_id];
	normalize_dist = 1.0 - ray.distance / (WINDOW_WIDTH * 0.8);
	if (ray.is_vertical_hit)
	{
		if (ray.is_facing_right)
			return (blend(0xFF0000, 0, normalize_dist));
		else
			return (blend(0x00FF00, 0, normalize_dist));
	}
	else
	{
		if (ray.is_facing_up)
			return (blend(0x0000FF, 0, normalize_dist));
		else
			return (blend(0xFFFF00, 0, normalize_dist));
	}
	return (0xFF00FF);
}

// Get perpendicular distance
float	perpendicular_distance(t_game *g, int ray_id)
{
	return (g->rays[ray_id].distance * cos(g->rays[ray_id].ray_angle
			- g->player.rot_angle));
}

void	render_walls(t_game *g)
{
	int		x;
	int		y;
	int		wall_height;
	float	distance_from_plane;
	float	projected_wall_height;
	int		wall_start_color;
	int		wall_end_color;
	int		color;

	x = 0;
	while (x < NUM_RAYS)
	{
		distance_from_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / perpendicular_distance(g, x))
			* distance_from_plane;
		wall_height = (int)projected_wall_height;
		wall_start_color = (WINDOW_HEIGHT / 2) - (wall_height / 2);
		wall_start_color = wall_start_color < 0 ? 0 : wall_start_color;
		wall_end_color = (WINDOW_HEIGHT / 2) + (wall_height / 2);
		wall_end_color = wall_end_color > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_end_color;
		y = wall_start_color;
		while (y < wall_end_color)
		{
			//color = get_color_from_texture(g, x);
			color = get_texture_color(g, x, y, wall_height);
			paint_pixel(g->frame.buffer, g->frame.line_length, x, y, color);
			y++;
		}
		x++;
	}
}

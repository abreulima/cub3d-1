/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:58:16 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 16:29:39 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static float	get_projected_wall_height(t_game *g, int x)
{
	float	distance_from_plane;

	distance_from_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	return ((TILE_SIZE / perpendicular_distance(g, x)) * distance_from_plane);
}

static void	get_wall_bounds(int wall_height, int *wall_start, int *wall_end)
{
	*wall_start = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	if (*wall_start < 0)
		*wall_start = 0;
	*wall_end = (WINDOW_HEIGHT / 2) + (wall_height / 2);
	if (*wall_end > WINDOW_HEIGHT)
		*wall_end = WINDOW_HEIGHT;
}

static void	draw_wall_slice(t_game *g, int x, t_wall_slice slice)
{
	int		y;
	int		color;
	t_point	point;

	y = slice.start;
	while (y < slice.end)
	{
		color = get_texture_color(g, x, y, slice.height);
		point.x = x;
		point.y = y;
		paint_pixel(g->frame.buffer, g->frame.line_length, point, color);
		y++;
	}
}

void	render_walls(t_game *g)
{
	int				x;
	t_wall_slice	slice;

	x = 0;
	while (x < NUM_RAYS)
	{
		slice.height = (int)get_projected_wall_height(g, x);
		get_wall_bounds(slice.height, &slice.start, &slice.end);
		draw_wall_slice(g, x, slice);
		x++;
	}
}

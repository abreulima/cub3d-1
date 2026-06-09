/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:57:56 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 17:31:50 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check of section of the ray is positioned at
// Check
void	init_ray_direction(float angle, t_ray_dir *dir)
{
	dir->is_ray_down = angle > 0 && angle < PI;
	dir->is_ray_up = !dir->is_ray_down;
	dir->is_ray_right = angle < 0.5 * PI || angle > 1.5 * PI;
	dir->is_ray_left = !dir->is_ray_right;
}

void	init_horizontal_step(t_game *g, t_ray_dir *dir, float angle, t_dda *h)
{
	h->y_intercept = floor(g->player.y / TILE_SIZE) * TILE_SIZE;
	if (dir->is_ray_down)
		h->y_intercept += TILE_SIZE;
	h->x_intercept = g->player.x + (h->y_intercept - g->player.y) / tan(angle);
	if (dir->is_ray_up)
		h->y_step = TILE_SIZE * -1;
	else
		h->y_step = TILE_SIZE;
	h->x_step = TILE_SIZE / tan(angle);
	if (dir->is_ray_left && h->x_step > 0)
		h->x_step *= -1;
	if (dir->is_ray_right && h->x_step < 0)
		h->x_step *= -1;
}

void	cast_horizontal_ray(t_game *g, t_ray_dir *dir, t_dda *h, t_hit *hit)
{
	float	x_check;
	float	y_check;

	hit->is_hit = 0;
	h->next_x = h->x_intercept;
	h->next_y = h->y_intercept;
	while (h->next_x >= 0 && h->next_x < g->map.w * TILE_SIZE && h->next_y >= 0
		&& h->next_y < g->map.h * TILE_SIZE)
	{
		x_check = h->next_x;
		y_check = h->next_y;
		if (dir->is_ray_up)
			y_check -= 1;
		if (check_wall_at(g, x_check, y_check))
		{
			hit->x = h->next_x;
			hit->y = h->next_y;
			hit->is_hit = 1;
			break ;
		}
		h->next_x += h->x_step;
		h->next_y += h->y_step;
	}
}

void	init_vertical_step(t_game *g, t_ray_dir *dir, float angle, t_dda *v)
{
	v->x_intercept = floor(g->player.x / TILE_SIZE) * TILE_SIZE;
	if (dir->is_ray_right)
		v->x_intercept += TILE_SIZE;
	v->y_intercept = g->player.y + (v->x_intercept - g->player.x) * tan(angle);
	if (dir->is_ray_left)
		v->x_step = TILE_SIZE * -1;
	else
		v->x_step = TILE_SIZE;
	v->y_step = TILE_SIZE * tan(angle);
	if (dir->is_ray_up && v->y_step > 0)
		v->y_step *= -1;
	if (dir->is_ray_down && v->y_step < 0)
		v->y_step *= -1;
}

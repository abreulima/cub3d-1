/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:32:09 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 17:32:20 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_vertical_ray(t_game *g, t_ray_dir *dir, t_dda *v, t_hit *hit)
{
	float	x_check;
	float	y_check;

	hit->is_hit = 0;
	v->next_x = v->x_intercept;
	v->next_y = v->y_intercept;
	while (v->next_x >= 0 && v->next_x < g->map.w * TILE_SIZE && v->next_y >= 0
		&& v->next_y < g->map.h * TILE_SIZE)
	{
		x_check = v->next_x;
		y_check = v->next_y;
		if (dir->is_ray_left)
			x_check -= 1;
		if (check_wall_at(g, x_check, y_check))
		{
			hit->x = v->next_x;
			hit->y = v->next_y;
			hit->is_hit = 1;
			break ;
		}
		v->next_x += v->x_step;
		v->next_y += v->y_step;
	}
}

void	store_ray_result(t_game *g, int id, t_hit *h_hit, t_hit *v_hit)
{
	float	h_dist;
	float	v_dist;

	h_dist = __FLT_MAX__;
	if (h_hit->is_hit)
		h_dist = distance_point2point(g->player.x, g->player.y,
				h_hit->x, h_hit->y);
	v_dist = __FLT_MAX__;
	if (v_hit->is_hit)
		v_dist = distance_point2point(g->player.x, g->player.y,
				v_hit->x, v_hit->y);
	if (v_dist < h_dist)
	{
		g->rays[id].distance = v_dist;
		g->rays[id].wall_hit_x = v_hit->x;
		g->rays[id].wall_hit_y = v_hit->y;
		g->rays[id].is_vertical_hit = 1;
	}
	else
	{
		g->rays[id].distance = h_dist;
		g->rays[id].wall_hit_x = h_hit->x;
		g->rays[id].wall_hit_y = h_hit->y;
		g->rays[id].is_vertical_hit = 0;
	}
}

void	store_ray_angles(t_game *g, int id, float angle, t_ray_dir *dir)
{
	g->rays[id].ray_angle = angle;
	g->rays[id].is_facing_down = dir->is_ray_down;
	g->rays[id].is_facing_up = dir->is_ray_up;
	g->rays[id].is_facing_left = dir->is_ray_left;
	g->rays[id].is_facing_right = dir->is_ray_right;
}

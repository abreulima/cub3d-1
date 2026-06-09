/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:57:59 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 07:58:00 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

float	normalize_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

float	distance_point2point(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(t_game *g, float angle, int id)
{
	t_ray_dir	dir;
	t_dda		h;
	t_dda		v;
	t_hit		h_hit;
	t_hit		v_hit;

	angle = normalize_angle(angle);
	init_ray_direction(angle, &dir);
	init_horizontal_step(g, &dir, angle, &h);
	cast_horizontal_ray(g, &dir, &h, &h_hit);
	init_vertical_step(g, &dir, angle, &v);
	cast_vertical_ray(g, &dir, &v, &v_hit);
	store_ray_result(g, id, &h_hit, &v_hit);
	store_ray_angles(g, id, angle, &dir);
}

void	cast_rays(t_game *g)
{
	int		i;
	float	ray_angle;

	ray_angle = g->player.rot_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(g, ray_angle, i);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}

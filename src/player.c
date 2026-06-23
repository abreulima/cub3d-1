/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:57:53 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/23 18:09:02 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

bool	check_wall_at(t_game *g, float x, float y)
{
	int	x_to_grid;
	int	y_to_grid;

	if (x < 0 || x >= g->map.w * TILE_SIZE || y < 0 || y >= g->map.h
		* TILE_SIZE)
		return (true);
	x_to_grid = floor(x / TILE_SIZE);
	y_to_grid = floor(y / TILE_SIZE);
	return (g->map.arr[y_to_grid][x_to_grid] == '1');
}

static bool	check_player_collision_at(t_game *g, float x, float y)
{
	float	left;
	float	right;
	float	top;
	float	bottom;

	left = x - (g->player.width / 2.0f) + 1.0f;
	right = x + (g->player.width / 2.0f) - 1.0f;
	top = y - (g->player.height / 2.0f) + 1.0f;
	bottom = y + (g->player.height / 2.0f) - 1.0f;
	return (check_wall_at(g, left, top)
		|| check_wall_at(g, right, top)
		|| check_wall_at(g, left, bottom)
		|| check_wall_at(g, right, bottom));
}

static void	handle_input(t_game *g, int *walk_dir_2)
{
	if (g->keys[W_KEY] == true)
		g->player.walk_dir = +1;
	if (g->keys[S_KEY] == true)
		g->player.walk_dir = -1;
	if (g->keys[D_KEY] == true)
		*walk_dir_2 = -1;
	if (g->keys[A_KEY] == true)
		*walk_dir_2 = +1;
	if (g->keys[RIGHT_ARROW] == true)
		g->player.turn_dir = +1;
	if (g->keys[LEFT_ARROW] == true)
		g->player.turn_dir = -1;
	if (g->keys[W_KEY] == false && g->keys[S_KEY] == false)
		g->player.walk_dir = 0;
	if (g->keys[A_KEY] == false && g->keys[D_KEY] == false)
		*walk_dir_2 = 0;
	if (g->keys[LEFT_ARROW] == false && g->keys[RIGHT_ARROW] == false)
		g->player.turn_dir = 0;
}

/*
static void apply_movement(t_game *g, int walk_dir_2)
{
float   move_step;
float   move_step_2;
float   new_y;
float   new_x;
g->player.rot_angle += g->player.turn_dir * g->player.turn_speed
* g->delta_time;
move_step = g->player.walk_dir * g->player.walk_speed * g->delta_time;
move_step_2 = walk_dir_2 * g->player.walk_speed * g->delta_time;
new_x = g->player.x + cos(g->player.rot_angle) * move_step
+ sin(g->player.rot_angle) * move_step_2;
new_y = g->player.y + sin(g->player.rot_angle) * move_step
+ cos(g->player.rot_angle) * move_step_2;
if (!check_wall_at(g, new_x, new_y))
    {
g->player.x = new_x;
g->player.y = new_y;
    }
}
*/

static void	apply_movement(t_game *g, int walk_dir_2)
{
	float	move_step;
	float	move_step_2;
	float	new_x;
	float	new_y;

	g->player.rot_angle += g->player.turn_dir * g->player.turn_speed
		* g->delta_time;
	move_step = g->player.walk_dir * g->player.walk_speed * g->delta_time;
	move_step_2 = walk_dir_2 * g->player.walk_speed * g->delta_time;
	new_x = g->player.x + cos(g->player.rot_angle) * move_step
		+ sin(g->player.rot_angle) * move_step_2;
	if (!check_player_collision_at(g, new_x, g->player.y))
		g->player.x = new_x;
	new_y = g->player.y + sin(g->player.rot_angle) * move_step
		- cos(g->player.rot_angle) * move_step_2;
	if (!check_player_collision_at(g, g->player.x, new_y))
	{
		g->player.y = new_y;
	}
}

void	move_player(t_game *g)
{
	int	walk_dir_2;

	walk_dir_2 = 0;
	handle_input(g, &walk_dir_2);
	apply_movement(g, walk_dir_2);
}
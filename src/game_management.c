/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-carv <jde-carv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:03:22 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/16 20:38:28 by jde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

int	game_loop(void *data)
{
	t_game	*g;

	g = (t_game *)data;
	move_player(g);
	cast_rays(g);
	render(g);
	return (0);
}

int	keydown(int keycode, t_game *g)
{
	g->keys[keycode] = true;
	if (keycode == ESC_KEY)
	{
		exit_game(g);
		exit(0);
	}
	return (0);
}

int	keyup(int keycode, t_game *g)
{
	g->keys[keycode] = false;
	return (0);
}

int	key_click_on_x(t_game *g)
{
	exit_game(g);
	exit(0);
}

void	load_textures(t_game *g, t_parse_data *data)
{
	g->map.walls[NORTH] = image_loader(g, data->tex_no);
	g->map.walls[SOUTH] = image_loader(g, data->tex_so);
	g->map.walls[EAST] = image_loader(g, data->tex_ea);
	g->map.walls[WEST] = image_loader(g, data->tex_we);
}

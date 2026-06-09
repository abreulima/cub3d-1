/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:58:08 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/09 15:26:19 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_player(t_player *p)
{
	p->x = 2 * TILE_SIZE;
	p->y = 2 * TILE_SIZE;
	p->height = 8;
	p->width = 8;
	p->turn_dir = 0;
	p->walk_dir = 0;
	p->rot_angle = 0;
	p->walk_speed = 100;
	p->turn_speed = 99999.0;
}

void	setup(t_game *g)
{
	setup_player(&g->player);
}

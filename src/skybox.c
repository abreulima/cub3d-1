/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:57:31 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 16:34:33 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_skybox(t_game *g, int sky, int floor)
{
	int		i;
	int		y;
	t_point	point;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			point.x = i;
			point.y = y;
			if (y > WINDOW_HEIGHT / 2)
				paint_pixel(g->frame.buffer, g->frame.line_length,
					point, sky);
			else
				paint_pixel(g->frame.buffer, g->frame.line_length,
					point, floor);
			y++;
		}
		i++;
	}
}

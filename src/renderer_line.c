/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:41:58 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 16:42:04 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	init_line_draw(t_line_draw *d, t_line line)
{
	d->delta_x = line.end_x - line.start_x;
	d->delta_y = line.end_y - line.start_y;
	d->pixels = sqrt((d->delta_x * d->delta_x)
			+ (d->delta_y * d->delta_y));
	if (d->pixels <= 0)
		return ;
	d->delta_x /= d->pixels;
	d->delta_y /= d->pixels;
	d->pixel_x = line.start_x;
	d->pixel_y = line.start_y;
}

void	paint_line(int *buff, int line_len, t_line line, int color)
{
	t_line_draw	d;
	t_point		p;

	init_line_draw(&d, line);
	if (d.pixels <= 0)
		return ;
	while (d.pixels--)
	{
		if (d.pixel_x < 0 || d.pixel_y < 0
			|| d.pixel_x >= WINDOW_WIDTH
			|| d.pixel_y >= WINDOW_HEIGHT)
			return ;
		p.x = (int)d.pixel_x;
		p.y = (int)d.pixel_y;
		paint_pixel(buff, line_len, p, color);
		d.pixel_x += d.delta_x;
		d.pixel_y += d.delta_y;
	}
}

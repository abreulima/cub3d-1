/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:58:06 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 17:24:49 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

void	paint_pixel(int *buff, int line_len, t_point p, int color)
{
	if (p.x < 0 || p.y < 0
		|| p.x >= WINDOW_WIDTH || p.y >= WINDOW_HEIGHT)
		return ;
	buff[(p.y * line_len) + p.x] = color;
}

void	paint_rect(int *buff, int line_len, t_rect r, int color)
{
	int		i;
	int		j;
	t_point	p;

	i = r.y;
	while (i < r.y + r.h)
	{
		j = r.x;
		while (j < r.x + r.w)
		{
			p.x = j;
			p.y = i;
			paint_pixel(buff, line_len, p, color);
			j++;
		}
		i++;
	}
}

void	clear_window(t_image_data *frame)
{
	int		i;
	int		j;
	int		*buf;
	t_point	p;

	buf = (int *)mlx_get_data_addr(frame->ptr,
			&frame->bits_per_pixel,
			&frame->line_length,
			&frame->endian);
	frame->line_length /= 4;
	i = 0;
	while (i < frame->height)
	{
		j = 0;
		while (j < frame->width)
		{
			p.x = j;
			p.y = i;
			paint_pixel(buf, frame->line_length, p, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

/*
void	*create_img_from_rect(t_game *g, void *source, int x, int y, int width,
		int height)
{
	int				*src_buffer;
	int				*dst_buffer;
	void			*target_img;
	t_image_data	src_data;
	t_image_data	dst_data;
	int				src_ll;
	int				dst_ll;
	t_rect			r;

	src_buffer = (int *)mlx_get_data_addr(source, &src_data.bits_per_pixel,
			&src_ll, &src_data.endian);
	src_ll /= 4;
	target_img = mlx_new_image(g->mlx.mlx, width, height);
	dst_buffer = (int *)mlx_get_data_addr(target_img, &dst_data.bits_per_pixel,
			&dst_ll, &dst_data.endian);
	dst_ll /= 4;
	r.x = x;
	r.y = y;
	r.w = width;
	r.h = height;
	copy_pixels(dst_buffer, src_buffer, dst_ll, src_ll, r);
	return ((void *)target_img);
}


void	paint_image(t_game *mlx, t_image_data *src, t_rect rect)
{
	int	*src_buffer;
	int	*buffer;
	int	x;
	int	y;
	int	pixel;

	src_buffer = (int *)mlx_get_data_addr(
		src->ptr,
		&src->bits_per_pixel,
		&src->line_length,
		&src->endian);
	src->line_length /= 4;
	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			pixel = src_buffer[(y * src->line_length) + x];
			//pixel = buffer_src[((y + src->y) * src->img_data.line_length) + (x
					+ src->x)];
			if (pixel == MAGENTA)
			{
				x++;
				continue ;
			}
			buffer[((y + (int)rect.y) * mlx->frame.line_length)
				+ (x + (int)rect.x)] = pixel;
			x++;
		}
		y++;
	}
}


void	paint_rect(int *buff, int line_len, t_rect rect, int color)
{
	int		i;
	int		j;
	t_point	point;

	i = rect.y;
	while (i < rect.y + rect.h)
	{
		j = rect.x;
		while (j < rect.x + rect.w)
		{
			point.x = j;
			point.y = i;
			paint_pixel(buff, line_len, point, color);
			j++;
		}
		i++;
	}
}

static void	init_line_draw(t_line_draw *d, t_line line)
{
	d->delta_x = line.end_x - line.start_x;
	d->delta_y = line.end_y - line.start_y;
	d->pixels = sqrt((d->delta_x * d->delta_x) + (d->delta_y * d->delta_y));
	if (d->pixels == 0)
		return ;
	d->delta_x /= d->pixels;
	d->delta_y /= d->pixels;
	d->pixel_x = line.start_x;
	d->pixel_y = line.start_y;
}

// https://gontjarow.github.io/MiniLibX/mlx-tutorial-draw-line.html
void	paint_line(int *buff, int line_len, t_line line, int color)
{
	t_line_draw	d;
	t_point		point;

	init_line_draw(&d, line);
	if (d.pixels == 0)
		return ;
	while (d.pixels > 0)
	{
		if (d.pixel_x < 0 || d.pixel_y < 0 || d.pixel_x >= WINDOW_WIDTH
			|| d.pixel_y >= WINDOW_HEIGHT)
			return ;
		point.x = (int)d.pixel_x;
		point.y = (int)d.pixel_y;
		paint_pixel(buff, line_len, point, color);
		d.pixel_x += d.delta_x;
		d.pixel_y += d.delta_y;
		d.pixels--;
	}
}


delta_x = line.end_x - line.start_x;
delta_y = line.end_y - line.start_y;
if	(abs(delta_x) >= abs(delta_y))
	step = abs(delta_x);
	else
	step = abs(delta_y);
	delta_x = delta_x / step;
delta_y = delta_y / step;
x = line.start_x;
y = line.end_x;
i = 0;
while (i < step)
{
	paint_pixel(buff, line_len, x, y, color);
	x += delta_x;
	y += delta_y;
	i++;
}


static void	paint_image_row(int *dst, int *src, int dst_ll, int src_ll,
		t_rect rect, int y)
{
	int	x;
	int	pixel;

	x = 0;
	while (x < rect.w)
	{
		pixel = src[(y * src_ll) + x];
		if (pixel != MAGENTA)
			dst[((y + (int)rect.y) * dst_ll) + (x + (int)rect.x)] = pixel;
		x++;
	}
}

void	paint_image(t_game *game, t_image_data *src, t_rect rect)
{
	int	*buffer;
	int	*src_buffer;
	int	src_ll;
	int	dst_ll;
	int	y;

	if (!src || !src->ptr)
		return ;
	printf("paint_image called: rect %d %d %d %d, src_ptr %p\n", rect.x, rect.y,
		rect.w, rect.h, src->ptr);
	buffer = (int *)mlx_get_data_addr(game->frame.ptr,
			&game->frame.bits_per_pixel, &dst_ll, &game->frame.endian);
	dst_ll /= 4;
	src_buffer = (int *)mlx_get_data_addr(src->ptr, &src->bits_per_pixel,
			&src_ll, &src->endian);
	src_ll /= 4;
	y = 0;
	while (y < rect.h)
	{
		paint_image_row(buffer, src_buffer, dst_ll, src_ll, rect, y);
		y++;
	}
}


https://stackoverflow.com/questions/24133131/loop-optimization-in-c
// Ensure ARRAY_SIZE is a multiple of two before trying this.
for (int i = 0; i < N_TIMES; i++)
for (int j = 0; j < ARRAY_SIZE; j += 2)
sum += array[j] + array[j+1];


void	clear_window(t_image_data *frame)
{
	int		i;
	int		j;
	int		*buffer;
	t_point	point;

	i = 0;
	buffer = (int *)mlx_get_data_addr(frame->ptr, &frame->bits_per_pixel,
			&frame->line_length, &frame->endian);
	frame->line_length /= 4;
	while (i < frame->height)
	{
		j = 0;
		while (j < frame->width)
		{
			point.x = j;
			point.y = i;
			paint_pixel(buffer, frame->line_length, point, 0xFFFFFF);
			j++;
		}
		i++;
	}
}
*/
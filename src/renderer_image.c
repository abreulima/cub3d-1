/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:43:49 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/09 15:49:15 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*create_img_from_rect(t_game *g, void *src, t_img_copy c)
{
	void			*img;
	t_image_data	srcd;
	t_image_data	dstd;

	c.src = (int *)mlx_get_data_addr(src, &srcd.bits_per_pixel, &c.src_ll,
			&srcd.endian);
	c.src_ll /= 4;
	img = mlx_new_image(g->mlx.mlx, c.w, c.h);
	c.dst = (int *)mlx_get_data_addr(img, &dstd.bits_per_pixel, &c.dst_ll,
			&dstd.endian);
	c.dst_ll /= 4;
	copy_pixels(c);
	return (img);
}

static void	blit_pixels(t_blit_ctx *ctx, t_rect rect)
{
	int	x;
	int	y;
	int	pixel;

	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			if (rect.x + x >= 0 && rect.y + y >= 0 && rect.x + x < WINDOW_WIDTH
				&& rect.y + y < WINDOW_HEIGHT)
			{
				pixel = ctx->src[(y * ctx->src_ll) + x];
				if (pixel != MAGENTA)
					ctx->dst[((y + rect.y) * ctx->dst_ll) + (x
							+ rect.x)] = pixel;
			}
			x++;
		}
		y++;
	}
}

void	paint_image(t_game *game, t_image_data *src, t_rect rect)
{
	t_blit_ctx	ctx;

	if (!src || !src->ptr)
		return ;
	ctx.dst = (int *)mlx_get_data_addr(game->frame.ptr,
			&game->frame.bits_per_pixel, &ctx.dst_ll, &game->frame.endian);
	ctx.src = (int *)mlx_get_data_addr(src->ptr, &src->bits_per_pixel,
			&ctx.src_ll, &src->endian);
	ctx.dst_ll /= 4;
	ctx.src_ll /= 4;
	blit_pixels(&ctx, rect);
}

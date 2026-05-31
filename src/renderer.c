#include "cub3d.h"
#include <math.h>
#define MAGENTA 0xFF00FF

void	paint_pixel(int *buff, int line_len, int x, int y, int color)
{
	if (y < 0 || x < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return ;
	buff[(y * line_len) + x] = color;
}

void	*create_img_from_rect(t_game *g, void *source, int x, int y, int width,
		int height)
{
	int				*src_buffer;
	int				*dst_buffer;
	void			*target_img;
	t_image_data	src_data;
	t_image_data	dst_data;
	int				i;
	int				j;

	src_buffer = (int *)mlx_get_data_addr(source, &src_data.bits_per_pixel,
			&src_data.line_length, &src_data.endian);
	target_img = mlx_new_image(g->mlx.mlx, width, height);
	dst_buffer = (int *)mlx_get_data_addr(target_img, &dst_data.bits_per_pixel,
			&dst_data.line_length, &dst_data.endian);
	dst_data.line_length /= 4;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			dst_buffer[(i * dst_data.line_length) + j] = src_buffer[((i + y)
					* src_data.line_length / 4) + j + x];
			j++;
		}
		i++;
	}
	return ((void *)target_img);
}

/*
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

*/
void	paint_rect(int *buff, int line_len, t_rect rect, int color)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.h)
	{
		j = rect.x;
		while (j < rect.x + rect.w)
		{
			// paint_rect(buff, line_len, j++, i, color);
			paint_pixel(buff, line_len, j, i, color);
			j++;
		}
		++i;
	}
}

// https://gontjarow.github.io/MiniLibX/mlx-tutorial-draw-line.html
void	paint_line(int *buff, int line_len, t_line line, int color)
{
	int		pixels;
	double	pixelX;
	double	pixelY;

	double deltaX = line.end_x - line.start_x; // 10
	double deltaY = line.end_y - line.start_y; // 0
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	pixelX = line.start_x;
	pixelY = line.start_y;
	while (pixels)
	{
		// mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		if (pixelY < 0 || pixelX < 0 || pixelX > WINDOW_WIDTH
			|| pixelY > WINDOW_HEIGHT)
			return ;
		paint_pixel(buff, line_len, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	/*
	delta_x = line.end_x - line.start_x;
	delta_y = line.end_y - line.start_y;
	if (abs(delta_x) >= abs(delta_y))
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
	*/
}

void	paint_image(t_game *game, t_image_data *src, t_rect rect)
{
	int	*buffer;
	int	*src_buffer;
	int	x;
	int	y;
	int	pixel;

	if (!src || !src->ptr)
		return ;
	buffer = (int *)mlx_get_data_addr(game->frame.ptr,
			&game->frame.bits_per_pixel, &game->frame.line_length,
			&game->frame.endian);
	game->frame.line_length /= 4;
	src_buffer = (int *)mlx_get_data_addr(src->ptr, &src->bits_per_pixel,
			&src->line_length, &src->endian);
	src->line_length /= 4;
	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			pixel = src_buffer[(y * src->line_length) + x];
			if (pixel == MAGENTA)
			{
				x++;
				continue ;
			}
			buffer[((y + (int)rect.y) * game->frame.line_length) + (x
					+ (int)rect.x)] = pixel;
			x++;
		}
		y++;
	}
}

/*
https://stackoverflow.com/questions/24133131/loop-optimization-in-c
// Ensure ARRAY_SIZE is a multiple of two before trying this.
for (int i = 0; i < N_TIMES; i++)
for (int j = 0; j < ARRAY_SIZE; j += 2)
sum += array[j] + array[j+1];
*/

void	clear_window(t_image_data *frame)
{
	int	i;
	int	j;
	int	*buffer;

	i = 0;
	buffer = (int *)mlx_get_data_addr(frame->ptr, &frame->bits_per_pixel,
			&frame->line_length, &frame->endian);
	frame->line_length /= 4;
	while (i < frame->height)
	{
		j = 0;
		while (j < frame->width)
		{
			paint_pixel(buffer, frame->line_length, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

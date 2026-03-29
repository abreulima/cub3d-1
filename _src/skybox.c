#include "cub3d.h"

void	render_skybox(t_game *g, int sky, int floor)
{
	int i;
	int y;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			if (y > WINDOW_HEIGHT / 2)
			paint_pixel(g->frame.buffer, g->frame.line_length, i, y, sky);
			else
			paint_pixel(g->frame.buffer, g->frame.line_length, i, y, floor);
			y++;
		}
		i++;
	}
}
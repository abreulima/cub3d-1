#include "cub3d.h"
#include <stdio.h>


static void	render_rays(t_game *g)
{
	int i;
	t_line line;

	i = 0;
	while (i < NUM_RAYS)
	{
		line = (t_line){
			g->player.x * SCALE + OFFSET,
			g->player.y * SCALE + +OFFSET,
			g->rays[i].wall_hit_x * SCALE + OFFSET,
			g->rays[i].wall_hit_y * SCALE + OFFSET,
		};
		paint_line(g->frame.buffer, g->frame.line_length, line, 0x0000FF);
		i++;
	}
}

static void	render_map(t_game *g)
{
	char tile;
	t_rect rect;

	for (int y = 0; y < g->map.h; y++)
	{
		for (int x = 0; x < g->map.w; x++)
		{
			rect = (t_rect){(x * TILE_SIZE * SCALE) + OFFSET, (y * TILE_SIZE
					* SCALE) + OFFSET, TILE_SIZE * SCALE, TILE_SIZE * SCALE};
			tile = g->map.arr[y][x];
			if (tile == '1')
				paint_rect(g->frame.buffer, g->frame.line_length, rect,
					0xFF00FF);
			else if (tile == 'P')
				paint_rect(g->frame.buffer, g->frame.line_length, rect,
					0xFFFFFF);
		}
	}
}

static void	render_player(t_game *g)
{
	t_rect rect;
	t_line line;

	rect = (t_rect){g->player.x * SCALE + OFFSET - (g->player.width / 2)
		* SCALE, g->player.y * SCALE + OFFSET - (g->player.height / 2) * SCALE,
		g->player.width * SCALE, g->player.height * SCALE};
	line = (t_line){(float)g->player.x * SCALE + OFFSET, (float)g->player.y
		* SCALE + OFFSET, (float)(g->player.x * SCALE + OFFSET
			+ cos(g->player.rot_angle) * 16.0), (float)(g->player.y * SCALE
			+ OFFSET + sin(g->player.rot_angle) * 16.0)};
	paint_rect(g->frame.buffer, g->frame.line_length, rect, 0xFF0000);
	paint_line(g->frame.buffer, g->frame.line_length, line, 0x000000);
}

void	render(t_game *g)
{
	clear_window(&g->frame);
	render_skybox(g, 0xFFAAFF, 0xFFCFAA);
	render_walls(g);
	render_map(g);
	render_rays(g);
	render_player(g);

	{
		// numero 4 esta faltando na font?????
		int degree = normalize_angle(g->player.rot_angle) * (180.0 / PI);
		render_text(g, ft_itoa(degree), (t_point){200, 128});
	}

	{
		render_text(g, "ide-abre", (t_point){200, 32});
		render_text(g, MSG_1, (t_point){200, 48});
		render_text(g, MSG_2, (t_point){200, 60});
		render_text(g, MSG_3, (t_point){200, 72});
	}
	paint_image(g, &g->images.crosshair, (t_rect){WINDOW_WIDTH / 2 - 16,
		WINDOW_HEIGHT / 2 - 16, 32, 32});
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.window, g->frame.ptr, 0, 0);
}

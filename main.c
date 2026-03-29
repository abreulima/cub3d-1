#include <cub3d.h>
#include <stdio.h>
#include <string.h>


int	game_loop(void *data)
{
	t_game *g;

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
		mlx_destroy_window(g->mlx.mlx, g->mlx.window);
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
	mlx_destroy_window(g->mlx.mlx, g->mlx.window);
	exit(0);
}

t_image_data	image_loader(t_game *g, char *path)
{
	t_image_data data;

	data.ptr = mlx_xpm_file_to_image(g->mlx.mlx, path, &data.width,
			&data.height);
	if (!data.ptr)
		return (data);
	data.buffer = (int *)mlx_get_data_addr(data.ptr, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	return (data);
}

int	main(void)
{
	t_game game;

	game.mlx.mlx = mlx_init();
	if (!game.mlx.mlx)
	{
		ft_putstr(ER_MLXINIT);
		return (-1);
	}
	game.mlx.window = mlx_new_window(game.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	game.frame.height = WINDOW_HEIGHT;
	game.frame.width = WINDOW_WIDTH;
	game.frame.ptr = mlx_new_image(game.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	game.delta_time = DELTA_TIME;

	// experimental
	game.frame.buffer = (int *)mlx_get_data_addr(game.frame.ptr,
			&game.frame.bits_per_pixel, &game.frame.line_length,
			&game.frame.endian);
	game.frame.line_length /= 4;

	game.images.crosshair = image_loader(&game, "_res/crosshair_2.xpm");

	game.images.font_tileset = image_loader(&game, "_res/def_font.xpm");

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			game.font[i + j * 16].ptr = create_img_from_rect(&game,
					game.images.font_tileset.ptr, (9 * i) + 1, 17 * j + 1, 8,
					16);
			game.font[i + j * 16].width = 8;
			game.font[i + j * 16].height = 16;
		}
	}

	char map[NUM_ROWS][NUM_COLS] = {{'1', '1', '1', '1', '1', '1', '1', '1',
		'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
									{'1', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '1'},
									{'1', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '1'},
									{'1', '0', '0', '0', '1', '0', '1', '0',
										'1', '0', '1', '0', '1', '0', '1', '0',
										'1', '0', '0', '1'},
									{'1', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '1'},
									{'1', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'1', '0', '0', '1'},
									{'1', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'1', '0', '0', '1'},
									{'1', '0', '0', '0', '0', '1', '1', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'1', '0', '0', '1'},
									{'1', '0', '0', '0', '1', '0', '0', '0',
										'0', '0', '0', '0', '0', '1', '1', '1',
										'1', '0', '0', '1'},
									{'1', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '1'},
									{'1', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '1'},
									{'1', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '0', '0', '0', '0', '0',
										'0', '0', '0', '1'},
									{'1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1'}};

	// game.map.arr = map_load(".cub", 10, 10);
	// game.map.arr = (char **)map;

	// Use memcpy to copy arr1 to arr2
	// memcpy(a, arr1, n * sizeof(arr1[0]));
	// arr = (int**)malloc(len);

	game.map.arr = malloc(sizeof(char *) * NUM_ROWS);
	// memcpy(game.map.arr, map, sizeof(char) * NUM_COLS * NUM_ROWS);

	for (int y = 0; y < NUM_ROWS; y++)
	{
		game.map.arr[y] = malloc(sizeof(char) * NUM_COLS);
	}

	for (int y = 0; y < NUM_ROWS; y++)
	{
		for (int x = 0; x < NUM_COLS; x++)
		{
			game.map.arr[y][x] = map[y][x];
		}
	}
	// return (0);

	game.map.w = NUM_COLS;
	game.map.h = NUM_ROWS;
	t_dict *dict = map_load("maps/hello.txt");
	if (!dict)
	{
		ft_putstr(ER_DUPLICATE);
		exit(EXIT_FAILURE);
	}
	if (test_for_textures(dict) == 0)
	{
		ft_putstr(ER_MISSINGVALUE);
		exit(EXIT_FAILURE);
	}
	
	if (load_texture(&game, dict) == -1)
	{
		ft_putstr(ER_NOFILE);
		exit(EXIT_FAILURE);
	}
	setup(&game);
	map_display(game.map.arr, game.map.w, game.map.h);
	mlx_loop_hook(game.mlx.mlx, &game_loop, &game);
	mlx_hook(game.mlx.window, 2, 1L << 0, keydown, &game);
	mlx_hook(game.mlx.window, 3, 1L << 1, keyup, &game);
	mlx_hook(game.mlx.window, 17, 0, key_click_on_x, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}

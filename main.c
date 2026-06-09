#include "cub3d.h"
#include "parsing.h"

static int	game_loop(void *data)
{
	t_game	*g;

	g = (t_game *)data;
	move_player(g);
	cast_rays(g);
	render(g);
	return (0);
}

static int	keydown(int keycode, t_game *g)
{
	g->keys[keycode] = true;
	if (keycode == ESC_KEY)
	{
		exit_game(g);
		exit(0);
	}
	return (0);
}

static int	keyup(int keycode, t_game *g)
{
	g->keys[keycode] = false;
	return (0);
}

static int	key_click_on_x(t_game *g)
{
	exit_game(g);
	exit(0);
}

static void	load_textures(t_game *g, t_parse_data *data)
{
	g->images.crosshair = image_loader(g, "res/crosshair_2.xpm");
	g->map.walls[NORTH] = image_loader(g, data->tex_no);
	g->map.walls[SOUTH] = image_loader(g, data->tex_so);
	g->map.walls[EAST] = image_loader(g, data->tex_ea);
	g->map.walls[WEST] = image_loader(g, data->tex_we);
}

static int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	apply_parse_data(t_game *g, t_parse_data *data)
{
	g->map.arr = data->map;
	g->map.w = data->map_w;
	g->map.h = data->map_h;
	g->map.floor_color = rgb_to_int(data->floor_r,
			data->floor_g, data->floor_b);
	g->map.ceiling_color = rgb_to_int(data->ceil_r,
			data->ceil_g, data->ceil_b);
	g->player.x = data->player_x * TILE_SIZE + TILE_SIZE / 2;
	g->player.y = data->player_y * TILE_SIZE + TILE_SIZE / 2;
	load_textures(g, data);
}

static float	get_player_angle(char dir)
{
	if (dir == 'N')
		return (3 * PI / 2);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'E')
		return (0);
	return (PI);
}

static int	init_mlx(t_game *g)
{
	g->mlx.mlx = mlx_init();
	if (!g->mlx.mlx)
		return (parse_error(E_MLX_INIT), -1);
	g->mlx.window = mlx_new_window(g->mlx.mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	g->frame.height = WINDOW_HEIGHT;
	g->frame.width = WINDOW_WIDTH;
	g->frame.ptr = mlx_new_image(g->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	g->frame.buffer = (int *)mlx_get_data_addr(g->frame.ptr,
			&g->frame.bits_per_pixel, &g->frame.line_length,
			&g->frame.endian);
	g->frame.line_length /= 4;
	g->delta_time = DELTA_TIME;
	return (0);
}

static void	setup_player_from_parse(t_game *g, t_parse_data *data)
{
	g->player.height = 8;
	g->player.width = 8;
	g->player.turn_dir = 0;
	g->player.walk_dir = 0;
	g->player.rot_angle = get_player_angle(data->player_dir);
	g->player.walk_speed = 100;
	g->player.turn_speed = 45 * (PI / 180);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_parse_data	data;

	if (argc != 2)
		return (parse_error(E_ARGS), 1);
	if (parse_file(argv[1], &data) == -1)
		return (1);
	ft_bzero(&game, sizeof(t_game));
	if (init_mlx(&game) == -1)
		return (free_parse_data(&data), 1);
	apply_parse_data(&game, &data);
	setup_player_from_parse(&game, &data);
	mlx_loop_hook(game.mlx.mlx, &game_loop, &game);
	mlx_hook(game.mlx.window, 2, 1L << 0, keydown, &game);
	mlx_hook(game.mlx.window, 3, 1L << 1, keyup, &game);
	mlx_hook(game.mlx.window, 17, 0, key_click_on_x, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}

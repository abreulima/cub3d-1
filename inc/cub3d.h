/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/06/08 17:33:57 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 17:33:57 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"
#include "libftutils.h"
#include "mlx.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <parsing.h>

#define MSG_1 "Welcome to our Cub3d. Enjoy!"
#define MSG_2 "There is no end, no begin."
#define MSG_3 "Your purpose is to press buttons."

#define PI 3.14159265
#define TWO_PI 6.28318530

#define NUM_COLS 20
#define NUM_ROWS 13

#define TILE_SIZE 32
//#define FOV_ANGLE (60.0 * (PI / 180.0))
#define FOV_ANGLE	1.0471975512
#define SCALE 0.25

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define OFFSET 10
#define MAGENTA 0xFF00FF

//#define WINDOW_WIDTH (NUM_COLS * TILE_SIZE)
//#define WINDOW_HEIGHT (NUM_ROWS * TILE_SIZE)

#define NUM_RAYS WINDOW_WIDTH

//#define DELTA_TIME (1.0 / 60.0)
#define DELTA_TIME	0.0166666667

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
}					t_mlx;

typedef struct s_player
{
	float			x;
	float			y;
	float			width;
	float			height;
	int				turn_dir;
	int				walk_dir;
	float			rot_angle;
	float			walk_speed;
	float			turn_speed;
}					t_player;

typedef struct s_image_data
{
	void			*ptr;
	int				height;
	int				width;
	int				*buffer;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_image_data;

typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_rect;

typedef struct s_line
{
	float			start_x;
	float			start_y;
	float			end_x;
	float			end_y;
}					t_line;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_crop
{
	int				x;
	int				y;
	int				width;
	int				height;
}					t_crop;

typedef struct s_line_draw
{
	int				pixels;
	double			delta_x;
	double			delta_y;
	double			pixel_x;
	double			pixel_y;
}					t_line_draw;

typedef struct s_map
{
	char			**arr;
	int				w;
	int				h;
	t_image_data	walls[4];
	int				floor_color;
	int				ceiling_color;
}					t_map;

typedef struct t_ray
{
	float			ray_angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			distance;
	int				is_vertical_hit;
	int				is_north;
	int				is_right;
	int				is_facing_up;
	int				is_facing_down;
	int				is_facing_left;
	int				is_facing_right;
	int				content;
}					t_ray;

typedef struct s_wall_slice
{
	int				start;
	int				end;
	int				height;
}					t_wall_slice;

typedef struct s_ray_dir
{
	int				is_ray_down;
	int				is_ray_up;
	int				is_ray_right;
	int				is_ray_left;
}					t_ray_dir;

typedef struct s_dda
{
	float			x_intercept;
	float			y_intercept;
	float			x_step;
	float			y_step;
	float			next_x;
	float			next_y;
}					t_dda;

typedef struct s_blit_ctx
{
	int				*dst;
	int				*src;
	int				dst_ll;
	int				src_ll;
}					t_blit_ctx;

typedef struct s_img_copy
{
	int				*src;
	int				*dst;
	int				x;
	int				y;
	int				w;
	int				h;
	int				src_ll;
	int				dst_ll;
}					t_img_copy;

typedef struct s_hit
{
	int				is_hit;
	float			x;
	float			y;
}					t_hit;

typedef struct s_images
{
	t_image_data	font_tileset;
	t_image_data	crosshair;
}					t_images;

typedef struct s_game
{
	t_mlx			mlx;
	t_player		player;
	t_map			map;
	float			delta_time;
	t_ray			rays[NUM_RAYS];
	bool			keys[65536];
	t_image_data	font[256];
	t_image_data	frame;
	t_images		images;
	t_parse_data 	*data;
}					t_game;

typedef enum e_walls
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}					t_walls;

typedef enum e_keys
{
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	ESC_KEY = 65307,
	LEFT_ARROW = 65361,
	RIGHT_ARROW = 65363
}					t_e_keys;

/*
MAC
typedef enum e_keys
{
	W_KEY = 13,
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	ESC_KEY = 53,
	LEFT_ARROW = 123,
	RIGHT_ARROW = 124
}					t_keys;
*/

t_dict				*map_load(char *path);
void				map_display(char **map, int x, int y);
void				map_delete(int **map, int x, int y);
void				render(t_game *g);
void				setup(t_game *g);
void				clear_window(t_image_data *frame);
void				move_player(t_game *g);

void				paint_rect(int *buff, int line_len, t_rect rect, int color);
// void	paint_line(int *buff, int line_len, t_line line, int color);
void				paint_line(int *buff, int line_len, t_line line, int color);
void				copy_pixels(t_img_copy c);
void				cast_rays(t_game *g);
bool				check_wall_at(t_game *g, float x, float y);
void				render_walls(t_game *g);
// void	paint_pixel(int *buff, int line_len, int x, int y, int color);
void				paint_pixel(int *buff, int line_len, t_point point,
						int color);

float				normalize_angle(float angle);
void				render_skybox(t_game *g, int sky, int floor);
void				paint_image(t_game *game, t_image_data *src, t_rect rect);
void				render_text(t_game *g, char *str, t_point point);
void				*create_img_from_rect(t_game *g, void *src, t_img_copy c);
void				copy_pixels(t_img_copy c);
int					load_texture(t_game *g, t_dict *dict);
t_image_data		image_loader(t_game *g, char *path);
int					get_texture_color(t_game *g, int ray_id, int y, int height);
unsigned int		blend(int main, int accent, float pct);
int					test_for_textures(t_dict *dict);
char				*ft_strtrim(const char *s1, const char *set);

float				distance_point2point(float x1, float y1, float x2,
						float y2);
float				normalize_angle(float angle);

void				init_ray_direction(float angle, t_ray_dir *dir);

void				store_ray_result(t_game *g, int id, t_hit *h_hit,
						t_hit *v_hit);
void				cast_vertical_ray(t_game *g, t_ray_dir *dir, t_dda *v,
						t_hit *hit);
void				init_vertical_step(t_game *g, t_ray_dir *dir, float angle,
						t_dda *v);
void				cast_horizontal_ray(t_game *g, t_ray_dir *dir, t_dda *v,
						t_hit *hit);
void				init_horizontal_step(t_game *g, t_ray_dir *dir, float angle,
						t_dda *h);
void				store_ray_angles(t_game *g, int id, float angle,
						t_ray_dir *dir);

float				perpendicular_distance(t_game *g, int ray_id);
int					get_color_from_texture(t_game *g, int ray_id);
unsigned int		blend(int main, int accent, float pct);
int 				exit_game(t_game *g);
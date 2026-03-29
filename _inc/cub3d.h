#include "../minilibx-linux/mlx.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilibft.h"
#include "dict.h"

#define MSG_1 "Welcome to our Cub3d. Enjoy!"
#define MSG_2 "There is no end, no begin."
#define MSG_3 "Your purpose is to press buttons."

#define ER_NOFILE "Error:\nUnable to load a file.\n"
#define ER_MAPERROR "Error:\nUnable to load map.\n"
#define ER_DUPLICATE "Error:\nKeys may be duplicated.\n"
#define ER_MISSINGVALUE "Error:\nMap is missing a value.\n"
#define ER_MISSPLAYER "Error:\nPlayer is missing.\n"
#define ER_MAPHOLES "Error:\nMap has holes.\n"
#define ER_MLXINIT "Error:\nUnable to init MLX.\n"


#define PI 3.14159265
#define TWO_PI 6.28318530

#define NUM_COLS 20
#define NUM_ROWS 13

#define TILE_SIZE 32
#define FOV_ANGLE 60 * (PI / 180)
#define SCALE 0.25

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define OFFSET 10

//#define WINDOW_WIDTH (NUM_COLS * TILE_SIZE)
//#define WINDOW_HEIGHT (NUM_ROWS * TILE_SIZE)


#define NUM_RAYS WINDOW_WIDTH

#define DELTA_TIME 1 / 60.0


typedef struct s_mlx
{
	void *mlx;
	void *window;
} t_mlx;

typedef struct s_player
{
	float x;
	float y;
	float width;
	float height;
	int turn_dir;
	int walk_dir;
	float rot_angle;
	float walk_speed;
	float turn_speed;
} t_player;

typedef struct s_image_data
{
	void *ptr;
	int height;
	int width;
	int *buffer;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_image_data;

typedef struct s_rect
{
	int x;
	int y;
	int w;
	int h;
} t_rect;

typedef struct s_line
{
	float start_x;
	float start_y;
	float end_x;
	float end_y;
} t_line;

typedef struct s_point
{
	int x;
	int y;
} t_point;

typedef struct s_map
{
	char **arr;
	int w;
	int h;
	t_image_data walls[4];
	int floor_color;
	int ceiling_color;
} t_map;

typedef struct t_ray
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	int is_vertical_hit;
	int is_north;
	int is_right;
	int is_facing_up;
	int is_facing_down;
	int is_facing_left;
	int is_facing_right;
	int content;
} t_ray;

typedef struct s_images
{
	t_image_data font_tileset;
	t_image_data crosshair;
} t_images;

typedef struct s_game
{
	t_mlx mlx;
	t_player player;
	t_map map;
	float delta_time;
	t_ray rays[NUM_RAYS];
	bool keys[65536];
	t_image_data font[256];
	t_image_data frame;
	t_images images;
} t_game;

typedef enum e_walls
{
	NORTH,
	SOUTH,
	EAST,
	WEST
} t_walls;

typedef enum e_keys
{
	A_KEY = 97,
	B_KEY = 98,
	C_KEY = 99,
	D_KEY = 100,
	E_KEY = 101,
	F_KEY = 102,
	G_KEY = 103,
	H_KEY = 104,
	I_KEY = 105,
	J_KEY = 106,
	K_KEY = 107,
	L_KEY = 108,
	M_KEY = 109,
	N_KEY = 110,
	O_KEY = 111,
	P_KEY = 112,
	Q_KEY = 113,
	R_KEY = 114,
	S_KEY = 115,
	T_KEY = 116,
	U_KEY = 117,
	V_KEY = 118,
	W_KEY = 119,
	X_KEY = 120,
	Y_KEY = 121,
	Z_KEY = 122,
	ESC_KEY = 65307,
	SHIFT_KEY = 65505,
	LEFT_ARROW = 65361,
	RIGHT_ARROW = 65363
} t_e_keys;

t_dict	*map_load(char *path);
void	map_display(char **map, int x, int y);
void	map_delete(int **map, int x, int y);
void	render(t_game *g);
void	setup(t_game *g);
void	clear_window(t_image_data *frame);
void	move_player(t_game *g);

void	paint_rect(int *buff, int line_len, t_rect rect, int color);
void	paint_line(int *buff, int line_len, t_line line, int color);
void	cast_rays(t_game *g);
bool	check_wall_at(t_game *g, float x, float y);
void	render_walls(t_game *g);
void	paint_pixel(int *buff, int line_len, int x, int y, int color);
float	normalize_angle(float angle);
void	render_skybox(t_game *g, int sky, int floor);
void	paint_image(t_game *game, t_image_data *src, t_rect rect);
void	render_text(t_game *g, char *str, t_point point);
void	*create_img_from_rect(t_game *g, void *source, int x, int y, int width,
		int height);
int		load_texture(t_game *g, t_dict *dict);
t_image_data	image_loader(t_game *g, char *path);
int	get_texture_color(t_game *g, int ray_id, int y, int height);
unsigned int	blend(int main, int accent, float pct);
int test_for_textures(t_dict *dict);
char	*ft_strtrim(const char *s1, const char *set);
#include "cub3d.h"
#include <stdio.h>

bool check_wall_at(t_game *g, float x, float y)
{
    int x_to_grid;
    int y_to_grid;

    if (x < 0 || x >= NUM_COLS * TILE_SIZE || y < 0 || y >= NUM_ROWS * TILE_SIZE)
        return true;
    x_to_grid = floor(x / TILE_SIZE);
    y_to_grid = floor(y / TILE_SIZE);
    return g->map.arr[y_to_grid][x_to_grid] == '1';
}

void move_player(t_game *g)
{
    int walk_dir_2;

    if (g->keys[W_KEY] == true)
        g->player.walk_dir = +1;
    if (g->keys[S_KEY] == true)
        g->player.walk_dir = -1;
    if (g->keys[D_KEY] == true)
        walk_dir_2 = -1;
    if (g->keys[A_KEY] == true)
        walk_dir_2 = +1;
    if (g->keys[RIGHT_ARROW] == true)
        g->player.turn_dir = +1;
    if (g->keys[LEFT_ARROW] == true)
        g->player.turn_dir = -1;


    if (g->keys[W_KEY] == false && g->keys[S_KEY] == false)
        g->player.walk_dir = 0;
    if (g->keys[A_KEY] == false && g->keys[D_KEY] == false)
        walk_dir_2 = 0;
    if (g->keys[LEFT_ARROW] == false && g->keys[RIGHT_ARROW] == false) 
        g->player.turn_dir = 0;

    g->player.rot_angle += g->player.turn_dir * g->player.turn_speed * g->delta_time;
    //g->player.rot_angle -= 1;

    float move_step = g->player.walk_dir * g->player.walk_speed * g->delta_time; 
    float move_step_2 = walk_dir_2 * g->player.walk_speed * g->delta_time; 


    float new_x = g->player.x + cos(g->player.rot_angle) * move_step + sin(g->player.rot_angle) * move_step_2;
    float new_y = g->player.y + sin(g->player.rot_angle) * move_step + cos(g->player.rot_angle) * move_step_2;

    
    
    if (!check_wall_at(g, new_x, new_y))
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }

}
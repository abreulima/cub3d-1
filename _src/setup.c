#include "cub3d.h"

static void setup_player(t_player *p)
{
    p->x = 2 * TILE_SIZE;
    p->y = 2 * TILE_SIZE;
    p->height = 8;
    p->width = 8;
    p->turn_dir = 0;
    p->walk_dir = 0;
    //p->rot_angle = PI / 2;
    //p->rot_angle = PI / 2;
    p->rot_angle = 0;
    p->walk_speed = 100;
    p->turn_speed = 10 * (PI / 180);
}

void setup_map(t_map *g)
{
    (void)g;
    //g->ceiling_color 
}

void setup(t_game *g)
{
    setup_map(&g->map);
    setup_player(&g->player);
}
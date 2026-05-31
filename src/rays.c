#include "cub3d.h"

#include <stdio.h>

float	normalize_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

float	distance_point2point(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(t_game *g, float angle, int id)
{
	bool	is_ray_down;
	bool	is_ray_up;
	bool	is_ray_right;
	bool	is_ray_left;
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	bool	is_horizontal_hit;
	float	horizontal_hit_x;
	float	horizontal_hit_y;
	int		horizontal_content_hit;
	float	next_horizontal_touch_x;
	float	next_horizontal_touch_y;
	float	x_to_check;
	float	y_to_check;
	bool	is_vertical_hit;
	float	vertical_hit_x;
	float	vertical_hit_y;
	int		vertical_content_hit;
	float	next_vertical_touch_x;
	float	next_vertical_touch_y;
	float	horizontal_hit_distance;
	float	vertical_hit_distance;

	angle = normalize_angle(angle);

	//printf("%f\n", angle  * (180 / PI));


	is_ray_down = angle > 0 && angle < PI;
    is_ray_up = !is_ray_down;

    is_ray_right = angle < 0.5 * PI || angle > 1.5 * PI;
    is_ray_left = !is_ray_right;
	//printf("%d %d\n", is_ray_down, is_ray_up);

	// horizontal wall
	is_horizontal_hit = false;
	horizontal_hit_x = 0;
	horizontal_hit_y = 0;
	horizontal_content_hit = 0;

	y_intercept = floor(g->player.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += is_ray_down ? TILE_SIZE : 0;
	
    x_intercept = g->player.x + (y_intercept - g->player.y) / tan(angle);
	
    y_step = TILE_SIZE;
	y_step *= is_ray_up ? -1 : 1;
	
    x_step = TILE_SIZE / tan(angle);
	x_step *= (is_ray_left && x_step > 0) ? -1 : 1;
	x_step *= (is_ray_right && x_step < 0) ? -1 : 1;
	
    next_horizontal_touch_x = x_intercept;
	next_horizontal_touch_y = y_intercept;
	
while (next_horizontal_touch_x >= 0
    && next_horizontal_touch_x < g->map.w * TILE_SIZE
    && next_horizontal_touch_y >= 0
    && next_horizontal_touch_y < g->map.h * TILE_SIZE)
	{
		x_to_check = next_horizontal_touch_x;
		y_to_check = next_horizontal_touch_y + (is_ray_up ? -1 : 0);
		if (check_wall_at(g, x_to_check, y_to_check))
		{
			// wall here
			horizontal_hit_x = next_horizontal_touch_x;
			horizontal_hit_y = next_horizontal_touch_y;
			//horizontal_content_hit = g->map.arr[(int)floor(y_to_check/ TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			is_horizontal_hit = true;
			break ;
		}
		else
		{
			next_horizontal_touch_x += x_step;
			next_horizontal_touch_y += y_step;
		}
	}
	// VERTICAL
	is_vertical_hit = false;
	vertical_hit_x = 0;
	vertical_hit_y = 0;
	vertical_content_hit = 0;

	x_intercept = floor(g->player.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += is_ray_right ? TILE_SIZE : 0;

	y_intercept = g->player.y + (x_intercept - g->player.x) * tan(angle);
	
    x_step = TILE_SIZE;
	x_step *= is_ray_left ? -1 : 1;

	y_step = TILE_SIZE * tan(angle);
	y_step *= (is_ray_up && y_step > 0) ? -1 : 1;
	y_step *= (is_ray_down && y_step < 0) ? -1 : 1;
	
    next_vertical_touch_x = x_intercept;
	next_vertical_touch_y = y_intercept;

while (next_vertical_touch_x >= 0
    && next_vertical_touch_x < g->map.w * TILE_SIZE
    && next_vertical_touch_y >= 0
    && next_vertical_touch_y < g->map.h * TILE_SIZE)
	{
		x_to_check = next_vertical_touch_x + (is_ray_left ? -1 : 0);
		y_to_check = next_vertical_touch_y;
		if (check_wall_at(g, x_to_check, y_to_check))
		{
			// wall here
			vertical_hit_x = next_vertical_touch_x;
			vertical_hit_y = next_vertical_touch_y;
			//vertical_content_hit = g->map.arr[(int)floor(y_to_check
			//		/ TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			is_vertical_hit = true;
			break ;
		}
		else
		{
			next_vertical_touch_x += x_step;
			next_vertical_touch_y += y_step;
		}
	}
	// Calculate both horizontal and vertical distance
	horizontal_hit_distance = is_horizontal_hit ? distance_point2point(g->player.x,
			g->player.y, horizontal_hit_x, horizontal_hit_y) : __FLT_MAX__;

	vertical_hit_distance = is_vertical_hit ? distance_point2point(g->player.x,
			g->player.y, vertical_hit_x, vertical_hit_y) : __FLT_MAX__;
	
    if (vertical_hit_distance < horizontal_hit_distance)
	{
		g->rays[id].distance = vertical_hit_distance;
		g->rays[id].wall_hit_x = vertical_hit_x;
		g->rays[id].wall_hit_y = vertical_hit_y;
		g->rays[id].content = vertical_content_hit;
		g->rays[id].is_vertical_hit = true;
	}
	else
	{
		g->rays[id].distance = horizontal_hit_distance;
		g->rays[id].wall_hit_x = horizontal_hit_x;
		g->rays[id].wall_hit_y = horizontal_hit_y;
		g->rays[id].content = horizontal_content_hit;
		g->rays[id].is_vertical_hit = false;
	}
	g->rays[id].ray_angle = angle;
	g->rays[id].is_facing_down = is_ray_down;
	g->rays[id].is_facing_up = is_ray_up;
	g->rays[id].is_facing_left = is_ray_left;
	g->rays[id].is_facing_right = is_ray_right;
}

void	cast_rays(t_game *g)
{
	int i;
	float ray_angle;

	ray_angle = g->player.rot_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(g, ray_angle, i);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}

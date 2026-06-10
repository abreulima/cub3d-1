/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:03:22 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/10 18:00:23 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_game_map(t_map *map)
{
	int	i;

	if (!map || !map->arr)
		return ;
	i = 0;
	while (i < map->h)
	{
		free(map->arr[i]);
		i++;
	}
	free(map->arr);
	map->arr = NULL;
	map->w = 0;
	map->h = 0;
}

void	free_image(void *mlx, t_image_data *img)
{
	if (!img || !img->ptr)
		return ;
	mlx_destroy_image(mlx, img->ptr);
	img->ptr = NULL;
	img->buffer = NULL;
}

void	free_walls(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free_image(g->mlx.mlx, &g->map.walls[i]);
		i++;
	}
}

void	free_images(t_game *g)
{
	free_image(g->mlx.mlx, &g->images.font_tileset);
	free_image(g->mlx.mlx, &g->images.crosshair);
	free_image(g->mlx.mlx, &g->frame);
}

void	cleanup(t_game *g)
{
	if (!g)
		return ;
	free_game_map(&g->map);
	free_walls(g);
	free_images(g);
	free_image(g->mlx.mlx, &g->frame);
	if (g->mlx.window)
		mlx_destroy_window(g->mlx.mlx, g->mlx.window);
	if (g->mlx.mlx)
	{
		mlx_destroy_display(g->mlx.mlx);
		free(g->mlx.mlx);
	}
}

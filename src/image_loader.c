/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:57:43 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 07:57:44 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image_data	image_loader(t_game *g, char *path)
{
	t_image_data	data;

	data.ptr = mlx_xpm_file_to_image(g->mlx.mlx, path, &data.width,
			&data.height);
	if (!data.ptr)
		return (data);
	data.buffer = (int *)mlx_get_data_addr(data.ptr, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	return (data);
}

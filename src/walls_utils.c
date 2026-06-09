/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:58:16 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 16:35:30 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

float	perpendicular_distance(t_game *g, int ray_id)
{
	return (g->rays[ray_id].distance * cos(g->rays[ray_id].ray_angle
			- g->player.rot_angle));
}

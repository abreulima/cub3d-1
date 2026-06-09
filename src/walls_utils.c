/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 07:58:16 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/09 19:31:11 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

float	perpendicular_distance(t_game *g, int ray_id)
{
	return (g->rays[ray_id].distance * cos(g->rays[ray_id].ray_angle
			- g->player.rot_angle));
}

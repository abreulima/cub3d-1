/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_image_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-abre <ide-abre@student.lista42.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:42:20 by ide-abre          #+#    #+#             */
/*   Updated: 2026/06/08 17:25:58 by ide-abre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_pixels(t_img_copy c)
{
	int	i;
	int	j;

	i = 0;
	while (i < c.h)
	{
		j = 0;
		while (j < c.w)
		{
			c.dst[(i * c.dst_ll) + j]
				= c.src[((i + c.y) * c.src_ll) + (j + c.x)];
			j++;
		}
		i++;
	}
}

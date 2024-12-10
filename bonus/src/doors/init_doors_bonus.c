/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:18:36 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/06 23:21:09 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	init_doors(t_cube *data)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->map.size)
	{
		x = 0;
		while (x < data->map.longest)
		{
			if (data->map._2d[y][x] == 'D')
			{
				if (add_to_list(data, (t_crd){x, y}))
					return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

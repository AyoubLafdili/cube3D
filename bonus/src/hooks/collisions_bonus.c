/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:35:56 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/30 17:50:08 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	check_next_door(t_cube *data, int x, int y)
{
	t_door	door;

	if (is_door(data->map._2d[y / CS][x / CS]))
	{
		door = get_rel_door(data, (t_crd){x, y})->door;
		if (door.is_open && !door.be_close)
			return (false);
		else
			return (true);
	}
	return (false);
}

bool	check_next_wall(t_cube *data, int x, int y)
{
	if (is_wall(data->map._2d[y / CS][x / CS]))
		return (true);
	else if (is_wall(data->map._2d[y / CS][(x + 5) / CS]))
		return (true);
	else if (is_wall(data->map._2d[y / CS][(x - 5) / CS]))
		return (true);
	else if (is_wall(data->map._2d[(y + 5) / CS][x / CS]))
		return (true);
	else if (is_wall(data->map._2d[(y - 5) / CS][x / CS]))
		return (true);
	return (false);
}

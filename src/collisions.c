/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:35:56 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/21 21:46:21 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_next_door(t_cube *data, int x, int y)
{
	t_door	door;

	if (data->map [y / CS][x / CS] == 'D')
	{
		door = get_related_door(data, (t_crd){x, y})->door;
		if (door.is_open && !door.be_close)
			return (false);
		else
			return (true);
	}
	return (false);
}

bool	check_next_wall(t_cube *data, int x, int y)
{
	if (data->map[y / CS][x / CS] == '1')
		return (true);
	else if (data->map[y / CS][(x + 10) / CS] == '1')
		return (true);
	else if (data->map[y / CS][(x - 10) / CS] == '1')
		return (true);
	else if (data->map[(y + 10) / CS][x / CS] == '1')
		return (true);
	else if (data->map[(y - 10) / CS][x / CS] == '1')
		return (true);
	return (false);
}

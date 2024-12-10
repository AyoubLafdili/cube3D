/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:05:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 23:01:36 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotation_handler(t_cube *data, t_direction dir)
{
	if (dir == T_RIGHT)
		data->player.rt_angle += (RT_SPEED * M_PI / 180);
	else
		data->player.rt_angle -= (RT_SPEED * M_PI / 180);
	check_angel(&data->player.rt_angle);
}

void	steps_handler(t_player player, t_direction dir, t_crd *next_pst)
{
	t_crd	new_crd;

	new_crd.x = MV_SPEED * cos(player.rt_angle);
	new_crd.y = MV_SPEED * sin(player.rt_angle);
	if (dir == UP)
	{
		next_pst->x = player.crd.x + new_crd.x;
		next_pst->y = player.crd.y + new_crd.y;
	}
	else if (dir == DOWN)
	{
		next_pst->x = player.crd.x - new_crd.x;
		next_pst->y = player.crd.y - new_crd.y;
	}
	else if (dir == RIGHT)
	{
		next_pst->x = player.crd.x - new_crd.y;
		next_pst->y = player.crd.y + new_crd.x;
	}
	else
	{
		next_pst->x = player.crd.x + new_crd.y;
		next_pst->y = player.crd.y - new_crd.x;
	}
}

bool	check_next(char **map, int x, int y)
{
	if (map[y / CS][x / CS] == '1')
		return (true);
	else if (map[y / CS][(x + 10) / CS] == '1')
		return (true);
	else if (map[y / CS][(x - 10) / CS] == '1')
		return (true);
	else if (map[(y + 10) / CS][x / CS] == '1')
		return (true);
	else if (map[(y - 10) / CS][x / CS] == '1')
		return (true);
	return (false);
}

void	mv_hdlr(t_cube *data, t_direction dir)
{
	t_crd	next_pst;

	if (dir == T_LEFT || dir == T_RIGHT)
		rotation_handler(data, dir);
	else
	{
		steps_handler(data->player, dir, &next_pst);
		if (check_next(data->map._2d, next_pst.x, next_pst.y))
			return ;
		data->player.crd.x = next_pst.x;
		data->player.crd.y = next_pst.y;
	}
}

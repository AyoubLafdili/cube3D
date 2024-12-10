/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handler_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:05:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/08 18:56:34 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	check_distance_to_door(t_cube *data)
{
	t_door_lst	*correspond_door;

	cast_ray_door(data, &data->door_ray);
	if (data->door_ray.distance <= P2D_DIST && data->door_ray.door_hit)
	{
		correspond_door = get_rel_door(data, data->door_ray.hit_crd);
		if (!correspond_door)
			return ;
		if (correspond_door->door.is_close)
			correspond_door->door.be_open = true;
		if (correspond_door->door.is_open)
			correspond_door->door.be_close = true;
	}
}

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
		next_pst->x = player.circle.center.x + new_crd.x;
		next_pst->y = player.circle.center.y + new_crd.y;
	}
	else if (dir == DOWN)
	{
		next_pst->x = player.circle.center.x - new_crd.x;
		next_pst->y = player.circle.center.y - new_crd.y;
	}
	else if (dir == RIGHT)
	{
		next_pst->x = player.circle.center.x - new_crd.y;
		next_pst->y = player.circle.center.y + new_crd.x;
	}
	else
	{
		next_pst->x = player.circle.center.x + new_crd.y;
		next_pst->y = player.circle.center.y - new_crd.x;
	}
}

void	mv_hdlr(t_cube *data, t_direction dir)
{
	t_crd	next_pst;

	if (dir == T_LEFT || dir == T_RIGHT)
		rotation_handler(data, dir);
	else
	{
		steps_handler(data->player, dir, &next_pst);
		if (check_next_wall(data, next_pst.x, next_pst.y)
			|| check_next_door(data, next_pst.x, next_pst.y))
			return ;
		data->player.circle.center.x = next_pst.x;
		data->player.circle.center.y = next_pst.y;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:05:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/21 22:35:50 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_distance_to_door(t_cube *data)
{
	t_door_lst	*correspond_door;

	cast_ray_door(data, &data->door_ray);
	if (data->door_ray.distance <= 180 && data->door_ray.door_hit)
	{
		printf("done\n");
		correspond_door = get_related_door(data, data->door_ray.hit_crd);
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
		data->player.rt_angel += (RT_SPEED * M_PI / 180);
	else
		data->player.rt_angel -= (RT_SPEED * M_PI / 180);
	check_angel(&data->player.rt_angel);
}

void	steps_handler(t_player player, t_direction dir, t_crd *next_pst)
{
	t_crd	new_crd;

	new_crd.x = (player.circle.radius + MV_SPEED) * cos(player.rt_angel);
	new_crd.y = (player.circle.radius + MV_SPEED) * sin(player.rt_angel);
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

void	moves_handler(t_cube *data, t_direction dir)
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

void	player_moves(void *param)
{
	t_cube	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		moves_handler(data, T_LEFT);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		moves_handler(data, T_RIGHT);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W)
		|| mlx_is_key_down(data->mlx, MLX_KEY_UP))
		moves_handler(data, UP);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		moves_handler(data, DOWN);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		moves_handler(data, RIGHT);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		moves_handler(data, LEFT);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
		check_distance_to_door(data);
}

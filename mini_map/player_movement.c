/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:05:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/14 18:08:25 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	moves_handler(t_cube *data, t_direction dir)
{
	t_crd	next_pst;

	if (dir == T_LEFT || dir == T_RIGHT)
		rotation_handler(data, dir);
	else
	{
		steps_handler(data->player, dir, &next_pst);
		if (check_next(data->map, next_pst.x, next_pst.y))
			return ;
		data->player.circle.center.x = next_pst.x;
		data->player.circle.center.y = next_pst.y;
	}
	rerendere_map(data);
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
}

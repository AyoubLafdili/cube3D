/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:05:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/25 20:57:20 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

bool check_radius(t_cube *data, t_crd new)
{
	int tmp;

	tmp = new.x;
	while (tmp <= new.x + data->player.circle.radius)
	{
		if (data->map[new.y / 60][tmp / 60] == '1')
			return (true);
		tmp++;
	}
	tmp = new.x;
	while (tmp >= new.x - data->player.circle.radius)
	{
		if (data->map[new.y / 60][tmp / 60] == '1')
			return (true);
		tmp--;
	}
	tmp = new.y;
	while (tmp <= new.y + data->player.circle.radius)
	{
		if (data->map[tmp / 60][new.x / 60] == '1')
			return (true);
		tmp++;
	}
	tmp = new.y;
	while (tmp >= new.y - data->player.circle.radius)
	{
		if (data->map[tmp / 60][new.x / 60] == '1')
			return (true);
		tmp--;
	}
	return (false);
}


void rotation_handler(t_cube *data, t_direction dir)
{
	if (dir == T_RIGHT)
		data->player.rt_angel += (20 * M_PI / 180);
	else
		data->player.rt_angel -= (20 * M_PI / 180);
	check_angel(data);
}

void steps_handler(t_cube *data, t_direction dir, t_crd *next_pst)
{
	t_crd new_crd;

	new_crd.x = (data->player.circle.radius + 5) * cos(data->player.rt_angel);
	new_crd.y = (data->player.circle.radius + 5) * sin(data->player.rt_angel);
	if (dir == M_UP)
	{
		next_pst->x = data->player.circle.center.x + new_crd.x;
		next_pst->y = data->player.circle.center.y + new_crd.y;
	}
	else if (dir == M_DOWN)
	{
		next_pst->x = data->player.circle.center.x - new_crd.x;
		next_pst->y = data->player.circle.center.y - new_crd.y;
	}
	else if (dir == M_RIGHT)
	{
		next_pst->x = data->player.circle.center.x - new_crd.y;
		next_pst->y = data->player.circle.center.y + new_crd.x;
	}
	else if (dir == M_LEFT)
	{
		next_pst->x = data->player.circle.center.x + new_crd.y;
		next_pst->y = data->player.circle.center.y - new_crd.x;
	}
}

void moves_handler(t_cube *data, t_direction dir)
{
	t_crd next_pst;

	if (dir == T_LEFT || dir == T_RIGHT)
		rotation_handler(data, dir);
	else
	{
		steps_handler(data, dir, &next_pst);
		if (check_radius(data, next_pst))
			return ;
		data->player.circle.center.x = next_pst.x;
		data->player.circle.center.y = next_pst.y;
	}
	rerendere_map(data);
}

void player_moves(mlx_key_data_t keydata, void *param)
{
	t_cube *data;

	data = param;
	if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
		return (moves_handler(data, T_LEFT));
	if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
		return (moves_handler(data, T_RIGHT));
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& keydata.action != MLX_RELEASE)
		return (moves_handler(data, M_UP));
	if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) 
		&& keydata.action != MLX_RELEASE)
		return (moves_handler(data, M_DOWN));
	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		return (moves_handler(data, M_RIGHT));
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		return (moves_handler(data, M_LEFT));
}

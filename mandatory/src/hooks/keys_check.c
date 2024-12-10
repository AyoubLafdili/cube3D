/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:20:37 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 02:08:39 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_both_down(mlx_t *mlx, keys_t k1, keys_t k2)
{
	return (mlx_is_key_down(mlx, k1) && mlx_is_key_down(mlx, k2));
}

static bool	special_moves(t_cube *data)
{
	if (is_both_down(data->mlx, MLX_KEY_W, MLX_KEY_RIGHT))
		return (mv_hdlr(data, UP), mv_hdlr(data, T_RIGHT), true);
	else if (is_both_down(data->mlx, MLX_KEY_W, MLX_KEY_LEFT))
		return (mv_hdlr(data, UP), mv_hdlr(data, T_LEFT), true);
	else if (is_both_down(data->mlx, MLX_KEY_S, MLX_KEY_RIGHT))
		return (mv_hdlr(data, DOWN), mv_hdlr(data, T_RIGHT), true);
	else if (is_both_down(data->mlx, MLX_KEY_S, MLX_KEY_LEFT))
		return (mv_hdlr(data, DOWN), mv_hdlr(data, T_LEFT), true);
	else if (is_both_down(data->mlx, MLX_KEY_W, MLX_KEY_D))
		return (mv_hdlr(data, UP), mv_hdlr(data, RIGHT), true);
	else if (is_both_down(data->mlx, MLX_KEY_W, MLX_KEY_A))
		return (mv_hdlr(data, UP), mv_hdlr(data, LEFT), true);
	else if (is_both_down(data->mlx, MLX_KEY_S, MLX_KEY_A))
		return (mv_hdlr(data, DOWN), mv_hdlr(data, LEFT), true);
	else if (is_both_down(data->mlx, MLX_KEY_S, MLX_KEY_D))
		return (mv_hdlr(data, DOWN), mv_hdlr(data, RIGHT), true);
	return (false);
}

void	player_moves(void *param)
{
	t_cube	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		close_callback(data);
	else if (special_moves(data))
		return ;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		mv_hdlr(data, T_LEFT);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		mv_hdlr(data, T_RIGHT);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W)
		|| mlx_is_key_down(data->mlx, MLX_KEY_UP))
		mv_hdlr(data, UP);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		mv_hdlr(data, DOWN);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		mv_hdlr(data, RIGHT);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		mv_hdlr(data, LEFT);
}

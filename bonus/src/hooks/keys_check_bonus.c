/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_check_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:40:45 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 21:43:25 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static inline bool	is_both_down(mlx_t *mlx, keys_t k1, keys_t k2)
{
	return (mlx_is_key_down(mlx, k1) && mlx_is_key_down(mlx, k2));
}

static bool	special_moves(t_cube *data)
{
	if (data->mini.sh_exp)
		return (true);
	else if (is_both_down(data->mlx, MLX_KEY_W, MLX_KEY_RIGHT))
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
	if (special_moves(data))
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
	usleep(1000);
}

void	independent_keys(mlx_key_data_t data, void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	if (data.key == MLX_KEY_ESCAPE)
		destroy_game(cube, EXIT_SUCCESS);
	else if (data.key == MLX_KEY_M && data.action == MLX_PRESS)
		cube->mini.sh_exp = !cube->mini.sh_exp;
	else if (data.key == MLX_KEY_E && !cube->mini.sh_exp)
		cube->should_animate = true;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_SPACE))
		check_distance_to_door(cube);
}

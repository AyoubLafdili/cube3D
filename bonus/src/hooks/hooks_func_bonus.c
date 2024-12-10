/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_func_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:59:06 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 21:45:21 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	close_callback(void *param)
{
	t_cube	*data;

	data = (t_cube *)param;
	destroy_game(data, EXIT_SUCCESS);
}

void	rerendere_map(void *param)
{
	t_cube	*data;

	data = (t_cube *)param;
	mini_map(data);
	open_door(data->head);
	close_door(data->head);
	cast_rays(data);
	_3d_rendering_(data);
	mlx_set_instance_depth(data->mt.mini_img->instances, 1);
	mlx_set_instance_depth(data->mt._3d_map->instances, 0);
	usleep(1000);
}

static inline int	put_img(t_cube *cube, mlx_image_t *sp, int w)
{
	return (mlx_image_to_window(cube->mlx, sp, w, W_HEIGHT - 460) == FAILED);
}

void	animate_sprite(void *param)
{
	static int	i;
	static int	repeat;
	t_cube		*cube;

	cube = (t_cube *)param;
	if (cube->should_animate)
	{
		if (!(++repeat % 2) && i++ < S_SIZE)
		{
			cube->mt.sprites[i]->enabled = true;
			if (put_img(cube, cube->mt.sprites[i], W_WIDHT / 4) == FAILED)
				return (ft_error("mlx", EMITWF), destroy_game(cube, 1));
			if (i > 0)
				cube->mt.sprites[i - 1]->enabled = false;
		}
	}
	if (i == S_SIZE - 1)
	{
		cube->mt.sprites[i]->enabled = false;
		i = 0;
		cube->should_animate = false;
	}
	usleep(1000);
}

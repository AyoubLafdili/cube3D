/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:06:58 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 21:41:13 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	destroy_game(t_cube *cube, bool status)
{
	if (cube->mt._3d_map)
		mlx_delete_image(cube->mlx, cube->mt._3d_map);
	if (cube->mt.mini_img)
		mlx_delete_image(cube->mlx, cube->mt.mini_img);
	del_prev(cube->mlx, cube->mt.sprites, cube->mt.sp_size);
	door_lst_clear(&cube->head);
	ft_clear_array(cube->map._2d);
	mlx_close_window(cube->mlx);
	mlx_terminate(cube->mlx);
	exit(status);
}

void	ft_clear_array(char **array)
{
	int				index;

	index = 0;
	if (!array)
		return ;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

void	del_prev(mlx_t *mlx, mlx_image_t *images[], t_cardin index)
{
	if (index <= 0)
		return ;
	mlx_delete_image(mlx, images[index]);
	del_prev(mlx, images, --index);
}

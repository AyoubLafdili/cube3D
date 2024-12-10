/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:06:58 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/06 22:41:16 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_game(t_cube *cube, bool status)
{
	if (cube->mt._3d_map)
		mlx_delete_image(cube->mlx, cube->mt._3d_map);
	mlx_close_window(cube->mlx);
	mlx_terminate(cube->mlx);
	ft_clear_array(cube->map._2d);
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

void	del_prev(t_cube *cube, t_cardin index)
{
	if (index <= 0)
		return ;
	mlx_delete_image(cube->mlx, cube->mt.images[index]);
	del_prev(cube, --index);
}

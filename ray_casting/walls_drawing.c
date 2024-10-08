/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:37:05 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/08 18:28:33 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_slice_drawing(mlx_image_t *img, double wall_height, double x)
{
	double	start_y;
	double	end_y;

	start_y = (W_HEIGHT / 2) - (wall_height / 2);
	end_y = (W_HEIGHT / 2) + (wall_height / 2);
	if (start_y < 0)
		start_y = 0;
	if (end_y > W_HEIGHT)
		end_y = W_HEIGHT;
	while (start_y < end_y)
		mlx_put_pixel(img, x, start_y++, WHITE);
}

void	walls_drawing(t_cube *data)
{
	double	distance_to_pp;
	double	wall_height;
	int		i;

	i = 0;
	data->_3d_map = mlx_new_image(data->mlx, W_WIDHT, W_HEIGHT);
	distance_to_pp = (W_WIDHT / 2) / tan(data->player.fov / 2);
	while (i < W_WIDHT)
	{
		wall_height = CELL_SZ * distance_to_pp / data->rays[i].distance;
		wall_slice_drawing(data->_3d_map, wall_height, i);
		i++;
	}
	mlx_image_to_window(data->mlx, data->_3d_map, 0, 0);
}

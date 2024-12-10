/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:47:06 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/06 18:26:37 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	symmetry_pixels(t_cube *data, int y, int x)
{
	int	cx;
	int	cy;

	cx = data->mini.size / 2;
	cy = data->mini.size / 2;
	while (y >= 0)
	{
		mlx_put_pixel(data->mt.mini_img, cx + x, cy + y, RED);
		mlx_put_pixel(data->mt.mini_img, cx + y, cy + x, RED);
		mlx_put_pixel(data->mt.mini_img, cx + y, cy - x, RED);
		mlx_put_pixel(data->mt.mini_img, cx + x, cy - y, RED);
		mlx_put_pixel(data->mt.mini_img, cx - x, cy - y, RED);
		mlx_put_pixel(data->mt.mini_img, cx - y, cy - x, RED);
		mlx_put_pixel(data->mt.mini_img, cx - y, cy + x, RED);
		mlx_put_pixel(data->mt.mini_img, cx - x, cy + y, RED);
		y--;
	}
}

void	draw_circle(t_cube *data)
{
	int	x;
	int	y;
	int	d_param;

	x = 0;
	if (data->mini.sh_exp)
		data->player.circle.radius = data->mini.sq_size / 1.6;
	else
		data->player.circle.radius = data->mini.sq_size / 3;
	y = data->player.circle.radius;
	d_param = 1 - data->player.circle.radius;
	symmetry_pixels(data, y, x);
	while (x < y)
	{
		if (d_param < 0)
		{
			d_param = d_param + (2 * x) + 3;
			symmetry_pixels(data, y, ++x);
		}
		else
		{
			d_param = d_param + (2 * (x - y)) + 5;
			symmetry_pixels(data, --y, ++x);
		}
	}
}

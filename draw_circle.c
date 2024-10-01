/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:47:06 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/26 10:59:41 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void symmetry_pixels(t_cube *data, int y, int x)
{
	int cx;
	int cy;

	cx = data->player.circle.center.x;
	cy = data->player.circle.center.y;
	while (y >= 0)
	{
		mlx_put_pixel(data->map_i, cx + x, cy + y, RED);
		mlx_put_pixel(data->map_i, cx + y, cy + x, RED);
		mlx_put_pixel(data->map_i, cx + y, cy - x, RED);
		mlx_put_pixel(data->map_i, cx + x, cy - y, RED);
		mlx_put_pixel(data->map_i, cx - x, cy - y, RED);
		mlx_put_pixel(data->map_i, cx - y, cy - x, RED);
		mlx_put_pixel(data->map_i, cx - y, cy + x, RED);
		mlx_put_pixel(data->map_i, cx - x, cy + y, RED);
		y--;
	}
}

void draw_circle(t_cube *data)
{
	int x;
	int y;
	int d_param;

	x = 0;
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
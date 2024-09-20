/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:22:52 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/17 13:22:52 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_cub(t_cube *data, int map_y, int map_x, int color)
{
	int y;
	int x;
	int save;

	y = x = 0;
	save = map_x;
	while (y < 60)
	{
		x = 0;
		map_x = save;
		while (x < 60)
		{
			mlx_put_pixel(data->map_i, map_x, map_y, color);
			x++;
			map_x++;
		}
		map_y++;
		y++;
	}
}

void symmetry_pixels(t_cube *data, int y, int x)
{
	int cx;
	int cy;

	cx = data->player.cx;
	cy = data->player.cy;
	while (y >= 0)
	{
		mlx_put_pixel(data->map_i, cx + x, cy + y, 0xFF0000FF);
		mlx_put_pixel(data->map_i, cx + y, cy + x, 0xFF0000FF);
		mlx_put_pixel(data->map_i, cx + y, cy - x, 0xFF0000FF);
		mlx_put_pixel(data->map_i, cx + x, cy - y, 0xFF0000FF);
		mlx_put_pixel(data->map_i, cx - x, cy - y, 0xFF0000FF);
		mlx_put_pixel(data->map_i, cx - y, cy - x, 0xFF0000FF);
		mlx_put_pixel(data->map_i, cx - y, cy + x, 0xFF0000FF);
		mlx_put_pixel(data->map_i, cx - x, cy + y, 0xFF0000FF);
		y--;
	}
}

void draw_player(t_cube *data, int radius)
{
	int x;
	int y;
	int param;

	x = 0;
	y = radius;
	param = 1 - radius;
	symmetry_pixels(data, y, x);
	while (x < y)
	{
		if (param < 0)
		{
			param = param + (2 * x) + 3;
			x += 1;
			symmetry_pixels(data, y, x);
		}
		else
		{
			param = param + (2 * (x - y)) + 5;
			x += 1;
			y -= 1;
			symmetry_pixels(data, y, x);
		}
	}
}

void draw_map(t_cube *data)
{
	int y;
	int x;

	data->map_i = mlx_new_image(data->mlx, WINDOW_WIDHT, WINDOW_HEIGHT);
	if (!data->map_i)
		return (ft_putendl_fd("Error: mlx_new_image failed!", 2));
	if (mlx_image_to_window(data->mlx, data->map_i, 0, 0))
		return (mlx_delete_image(data->mlx, data->map_i), 
			ft_putendl_fd("Error: mlx_image_to_window failed!", 2));
	y = x = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_cub(data, y * 60, x * 60 , 0x000000FF);
			else if (data->map[y][x] == '0')
				draw_cub(data, y * 60, x * 60, 0xFFFFFFFF);
			else if (data->map[y][x] == 'P')
			{
				draw_cub(data, y * 60, x * 60, 0xFFFFFFFF);
				data->player.px = x * 60 + (60 / 2);
				data->player.py = y * 60 + (60 / 2);
			}
			x++;
		}
		y++;
	}    
}

int main()
{
	t_cube data;
	char *map[] = { 
		"1111111",
		"1100111",
		"1000101",
		"1010001",
		"1010001",
		"1000001",
		"1001001",
		"10000P1",
		"1111111",
		NULL
		};
	ft_memset(&data, 0, sizeof(t_cube));
	data.map = map;
	data.player.rt_angel = M_PI / 2;
	data.player.radius = 8;
	data.mlx = mlx_init(WINDOW_WIDHT, WINDOW_HEIGHT, "cub3d", 1);
	if (!data.mlx)
	   printf("mlx_init");
	draw_map(&data);
	data.player.cx = data.player.px;
	data.player.cy = data.player.py;
	draw_player(&data, data.player.radius);
	mlx_loop(data.mlx);
	return (0);
}
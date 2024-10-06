/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:11:38 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/27 22:47:53 by alafdili         ###   ########.fr       */
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
	while (y < TILE_SIZE)
	{
		x = 0;
		map_x = save;
		while (x < TILE_SIZE)
		{
			mlx_put_pixel(data->map_i, map_x, map_y, color);
			x++;
			map_x++;
		}
		map_y++;
		y++;
	}
}

void check_player_view(t_cube *data, int x, int y)
{
	static bool angle_update;

	if (data->map[y][x] == 'N' && !angle_update)
		data->player.rt_angel = 3 * M_PI_2;
	else if (data->map[y][x] == 'S' && !angle_update)
		data->player.rt_angel = M_PI_2;
	else if (data->map[y][x] == 'E' && !angle_update)
		data->player.rt_angel = 0;
	else if (data->map[y][x] == 'W' && !angle_update)
		data->player.rt_angel = M_PI;
	draw_cub(data, y * TILE_SIZE, x * TILE_SIZE, WHITE);
	data->player.circle.radius = 4;
	data->player.p_crd.x = x * TILE_SIZE + (TILE_SIZE / 2);
	data->player.p_crd.y = y * TILE_SIZE + (TILE_SIZE / 2);
	angle_update = true;
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
				draw_cub(data, y * TILE_SIZE, x * TILE_SIZE , BLACK);
			else if (data->map[y][x] == '0')
				draw_cub(data, y * TILE_SIZE, x * TILE_SIZE, WHITE);
			else
				check_player_view(data, x, y);
			x++;
		}
		y++;
	}
}

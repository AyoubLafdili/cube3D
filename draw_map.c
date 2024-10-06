/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:11:38 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/05 19:20:42 by alafdili         ###   ########.fr       */
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
	while (y < MAP_SCALE)
	{
		x = 0;
		map_x = save;
		while (x < MAP_SCALE)
		{
			mlx_put_pixel(data->mini_map, map_x, map_y, color);
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
	draw_cub(data, y * MAP_SCALE, x * MAP_SCALE, WHITE);
	data->player.circle.radius = 2;
	angle_update = true;
}

void draw_map(t_cube *data)
{
	int y;
	int x;

	data->mini_map = mlx_new_image(data->mlx, WINDOW_WIDHT, WINDOW_HEIGHT);
	if (!data->mini_map)
		return (ft_putendl_fd("Error: mlx_new_image failed!", 2));
	if (mlx_image_to_window(data->mlx, data->mini_map, 0, 0))
		return (mlx_delete_image(data->mlx, data->mini_map), 
			ft_putendl_fd("Error: mlx_image_to_window failed!", 2));
	y = x = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_cub(data, y * MAP_SCALE, x * MAP_SCALE , BLACK);
			else if (data->map[y][x] == '0')
				draw_cub(data, y * MAP_SCALE, x * MAP_SCALE, WHITE);
			else
				check_player_view(data, x, y);
			x++;
		}
		y++;
	}
}

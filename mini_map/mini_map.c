/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:11:38 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/08 18:23:30 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	circle_or_line_init(t_player *player, int x, int y)
{
	if (x > 0 && y > 0)
	{
		player->circle.radius = 2;
		player->circle.center.x = x * CELL_SZ + (CELL_SZ / 2);
		player->circle.center.y = y * CELL_SZ + (CELL_SZ / 2);
		return ;
	}
	player->line.start.x = player->circle.center.x * 0.2;
	player->line.start.y = player->circle.center.y * 0.2;
	player->line.end.x = player->line.start.x + 10 * cos(player->rt_angel);
	player->line.end.y = player->line.start.y + 10 * sin(player->rt_angel);
}

void	draw_cub(t_cube *data, int map_y, int map_x, int color)
{
	int	y;
	int	x;
	int	save;

	y = 0;
	x = y;
	save = map_x;
	while (y < 0.2 * CELL_SZ)
	{
		x = 0;
		map_x = save;
		while (x < 0.2 * CELL_SZ)
		{
			mlx_put_pixel(data->mini_map, map_x, map_y, color);
			x++;
			map_x++;
		}
		map_y++;
		y++;
	}
}

void	check_player_view(t_cube *data, int x, int y)
{
	static bool	angle_update;

	if (data->map[y][x] == 'N' && !angle_update)
		data->player.rt_angel = 3 * M_PI_2;
	else if (data->map[y][x] == 'S' && !angle_update)
		data->player.rt_angel = M_PI_2;
	else if (data->map[y][x] == 'E' && !angle_update)
		data->player.rt_angel = 0;
	else if (data->map[y][x] == 'W' && !angle_update)
		data->player.rt_angel = M_PI;
	if (!angle_update)
		circle_or_line_init(&data->player, x, y);
	draw_cub(data, y * 0.2 * CELL_SZ, x * 0.2 * CELL_SZ, T_WHITE);
	angle_update = true;
}

void	draw_map(t_cube *data)
{
	int	y;
	int	x;

	y = 0;
	x = y;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_cub(data, y * 0.2 * CELL_SZ, x * 0.2 * CELL_SZ, BLACK);
			else if (data->map[y][x] == '0')
				draw_cub(data, y * 0.2 * CELL_SZ, x * 0.2 * CELL_SZ, T_WHITE);
			else
				check_player_view(data, x, y);
			x++;
		}
		y++;
	}
}

void	mini_map(t_cube *data)
{
	data->mini_map = mlx_new_image(data->mlx, W_WIDHT * 0.2, W_HEIGHT * 0.2);
	if (!data->mini_map)
		return (ft_putendl_fd("Error: mlx_new_image failed!", 2));
	if (mlx_image_to_window(data->mlx, data->mini_map, 0, 0))
		return (mlx_delete_image(data->mlx, data->mini_map),
			ft_putendl_fd("Error: mlx_image_to_window failed!", 2));
	draw_map(data);
	draw_circle(data);
	circle_or_line_init(&data->player, -1, -1);
	draw_line(data, &data->player.line);
}

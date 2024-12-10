/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:11:38 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 22:23:06 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	line_init(t_line *line, t_mini mini, double rt_angle)
{
	int	len;

	if (mini.sh_exp)
		len = mini.sq_size * 2;
	else
		len = mini.sq_size;
	line->start.x = mini.size / 2;
	line->start.y = mini.size / 2;
	line->end.x = line->start.x + len * cos(rt_angle);
	line->end.y = line->start.y + len * sin(rt_angle);
}

void	init_mini_params(t_crd player, t_mini *mini)
{
	float	distance;

	mini->size = 200 * !mini->sh_exp;
	mini->i_pst.x = 30 * !mini->sh_exp;
	mini->i_pst.y = 30 * !mini->sh_exp;
	mini->sq_size = mini->size / 20 * !mini->sh_exp;
	if (mini->sh_exp)
	{
		mini->size = W_WIDHT / 2;
		mini->i_pst.x = W_WIDHT / 4;
		mini->i_pst.y = (W_HEIGHT - W_WIDHT / 2) / 2;
		mini->sq_size = mini->size / 52;
	}
	mini->start.x = player.x - ((mini->sq_size / 2) * CS);
	mini->start.y = player.y - ((mini->sq_size / 2) * CS);
	distance = (mini->start.x + (mini->sq_size * CS)) - mini->start.x;
	mini->min_fact = distance / mini->size;
}

void	put_px(t_cube *data, int map_x, int map_y, t_crd pixels)
{
	if (map_x >= data->map.longest - 1 || map_x <= 0
		|| map_y >= data->map.size || map_y <= 0)
		mlx_put_pixel(data->mt.mini_img, pixels.x, pixels.y, BLACK);
	else if (is_wall(data->map._2d[map_y][map_x])
		|| is_space(data->map._2d[map_y][map_x]))
		mlx_put_pixel(data->mt.mini_img, pixels.x, pixels.y, BLACK);
	else if (is_door(data->map._2d[map_y][map_x]))
		mlx_put_pixel(data->mt.mini_img, pixels.x, pixels.y, RED);
	else if (is_zero(data->map._2d[map_y][map_x])
		|| is_player(data->map._2d[map_y][map_x]))
		mlx_put_pixel(data->mt.mini_img, pixels.x, pixels.y, T_WHITE);
}

void	draw_mini_map(t_cube *data, t_mini *mini)
{
	double	x_inc;
	int		y;
	int		x;

	y = 0;
	while (y < mini->size)
	{
		x = 0;
		x_inc = mini->start.x;
		while (x < mini->size)
		{
			put_px(data, x_inc / CS, mini->start.y / CS, (t_crd){x, y});
			x_inc += mini->min_fact;
			x++;
		}
		y++;
		mini->start.y += mini->min_fact;
	}
}

void	mini_map(t_cube *data)
{
	init_mini_params(data->player.circle.center, &data->mini);
	mlx_resize_image(data->mt.mini_img, data->mini.size, data->mini.size);
	data->mt.mini_img->instances[0].x = data->mini.i_pst.x;
	data->mt.mini_img->instances[0].y = data->mini.i_pst.y;
	draw_mini_map(data, &data->mini);
	draw_circle(data);
	line_init(&data->player.line, data->mini, data->player.rt_angle);
	draw_line(data, data->player.line);
}

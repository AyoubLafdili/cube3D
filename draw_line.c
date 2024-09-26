/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:49:25 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/26 10:37:20 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_line(t_cube *data, t_line *line)
{
	line->start.x = data->player.circle.center.x;
	line->start.y = data->player.circle.center.y;
	line->end.x = line->start.x + 25 * cos(data->player.rt_angel); 
	line->end.y = line->start.y + 25 * sin(data->player.rt_angel); 
}

void l_than_one(t_cube *data, t_crd start, t_crd end)
{
	int		dy;
	int		dx;
	t_crd	sign;
	int		d_param;

	dy = abs(end.y - start.y);
	dx = abs(end.x - start.x);
	sign.y = ft_sign(end.y - start.y);
	sign.x = ft_sign(end.x - start.x);
	d_param = 2 * dy - dx;
	mlx_put_pixel(data->map_i, start.x, start.y, blue);
	while (start.x < end.x)
	{
		start.x += sign.x;
		if (d_param < 0)
			d_param += 2 * dy;
		else
		{
			start.y += sign.y;
			d_param += (2 * dy) - (2 * dx);
		}
		mlx_put_pixel(data->map_i, start.x, start.y, blue);
	}
}

void g_than_one(t_cube *data, t_crd start, t_crd end)
{
	int dy;
	int dx;
	t_crd sign;
	int d_param;

	dy = abs(end.y - start.y);
	dx = abs(end.x - start.x);
	sign.y = ft_sign(end.y - start.y);
	sign.x = ft_sign(end.x - start.x);
	d_param = 2 * dy - dx;
	mlx_put_pixel(data->map_i, start.y, start.x, blue);
	while (start.x < end.x)
	{
		start.x += sign.x;
		if (d_param < 0)
			d_param += 2 * dy;
		else
		{
			start.y += sign.y;
			d_param += (2 * dy) - (2 * dx);
		}
		mlx_put_pixel(data->map_i, start.y, start.x, blue);
	}
}


void draw_line(t_cube *data, t_line *ln)
{
	int dy;
	int dx;
	float slope;

	init_line(data, ln);
	dy = ln->end.y - ln->start.y;
	dx = ln->end.x - ln->start.x;
	slope = fabs(dy / (float)dx);
	if (slope < 1)
	{
		if (ln->start.x > ln->end.x)
			l_than_one(data, ln->end, ln->start);
		else
			l_than_one(data, ln->start, ln->end);
	}
	else
	{
		ft_swap(&ln->start.y, &ln->start.x);
		ft_swap(&ln->end.y, &ln->end.x);
		if (ln->start.x < ln->end.x)
			g_than_one(data, ln->start, ln->end);
		else
			g_than_one(data, ln->end, ln->start);
	}
}

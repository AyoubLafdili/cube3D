/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:49:25 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 22:22:24 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	less_than_one(t_cube *data, t_crd start, t_crd end)
{
	double		dy;
	double		dx;
	t_crd		sign;
	double		d_param;

	dy = fabs(end.y - start.y);
	dx = fabs(end.x - start.x);
	sign.y = ft_sign(end.y - start.y);
	sign.x = ft_sign(end.x - start.x);
	d_param = 2 * dy - dx;
	mlx_put_pixel(data->mt.mini_img, start.x, start.y, BLUE);
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
		mlx_put_pixel(data->mt.mini_img, start.x, start.y, BLUE);
	}
}

void	greater_than_one(t_cube *data, t_crd start, t_crd end)
{
	double	dy;
	double	dx;
	t_crd	sign;
	double	d_param;

	dy = fabs(end.y - start.y);
	dx = fabs(end.x - start.x);
	sign.y = ft_sign(end.y - start.y);
	sign.x = ft_sign(end.x - start.x);
	d_param = 2 * dy - dx;
	mlx_put_pixel(data->mt.mini_img, start.y, start.x, BLUE);
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
		mlx_put_pixel(data->mt.mini_img, start.y, start.x, BLUE);
	}
}

void	draw_line(t_cube *data, t_line ln)
{
	double	dy;
	double	dx;
	double	slope;

	dy = ln.end.y - ln.start.y;
	dx = ln.end.x - ln.start.x;
	slope = fabs(dy / dx);
	if (slope < 1)
	{
		if (ln.start.x > ln.end.x)
			less_than_one(data, ln.end, ln.start);
		else
			less_than_one(data, ln.start, ln.end);
	}
	else
	{
		ft_swap(&ln.start.y, &ln.start.x);
		ft_swap(&ln.end.y, &ln.end.x);
		if (ln.start.x < ln.end.x)
			greater_than_one(data, ln.start, ln.end);
		else
			greater_than_one(data, ln.end, ln.start);
	}
}

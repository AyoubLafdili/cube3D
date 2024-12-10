/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_drawing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:37:05 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/08 18:57:45 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	sky_drawing(t_cube *data, int end, int x)
{
	int	start;

	start = 0;
	while (start < end)
	{
		mlx_put_pixel(data->mt._3d_map, x, start, data->mt.colors[C]);
		start++;
	}
}

void	floor_drawing(t_cube *data, int start, int x)
{
	while (start < W_HEIGHT)
	{
		mlx_put_pixel(data->mt._3d_map, x, start, data->mt.colors[F]);
		start++;
	}
}

void	wall_drawing(t_cube *data, double w_height, int i, uint32_t mtx[CS][CS])
{
	t_crd	idx;
	int		end_y;
	int		y_inc;
	int		start_y;

	start_y = (W_HEIGHT / 2) - (w_height / 2);
	end_y = (W_HEIGHT / 2) + (w_height / 2);
	y_inc = start_y;
	idx.x = calc_offset(data->rays[i].hit_crd, !data->rays[i].vert_hit);
	if (data->rays[i].door_hit)
		idx.x -= get_offset(data, i);
	wall_height_reset(&y_inc, &end_y);
	while (y_inc < end_y)
	{
		idx.y = (y_inc - start_y) * (CS / w_height);
		mlx_put_pixel(data->mt._3d_map, i, y_inc, mtx[(int)idx.y][(int)idx.x]);
		y_inc++;
	}
}

void	_slice_drawing(t_cube *data, double wall_height, int i)
{
	t_ray	ray;
	int		end_y;
	int		start_y;

	ray = data->rays[i];
	start_y = (W_HEIGHT / 2) - (wall_height / 2);
	end_y = (W_HEIGHT / 2) + (wall_height / 2);
	if (ray.door_hit)
		wall_drawing(data, wall_height, i, data->mt.tex_buf[DO]);
	else if (ray.vert_hit && ray_direction(ray.angle, true) == LEFT)
		wall_drawing(data, wall_height, i, data->mt.tex_buf[NO]);
	else if (ray.vert_hit && ray_direction(ray.angle, true) == RIGHT)
		wall_drawing(data, wall_height, i, data->mt.tex_buf[SO]);
	else if (!ray.vert_hit && ray_direction(ray.angle, false) == UP)
		wall_drawing(data, wall_height, i, data->mt.tex_buf[EA]);
	else
		wall_drawing(data, wall_height, i, data->mt.tex_buf[WE]);
	wall_height_reset(&start_y, &end_y);
	sky_drawing(data, start_y, i);
	floor_drawing(data, end_y, i);
}

void	_3d_rendering_(t_cube *data)
{
	int		i;
	double	wall_height;
	double	distance_to_pp;

	i = 0;
	distance_to_pp = (W_WIDHT / 2.0) / tan(data->player.fov / 2);
	while (i < W_WIDHT)
	{
		wall_height = CS * distance_to_pp / data->rays[i].distance;
		_slice_drawing(data, wall_height, i);
		i++;
	}
}

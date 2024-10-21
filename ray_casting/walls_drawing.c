/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:37:05 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/21 18:45:00 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sky_drawing(mlx_image_t *_3d_plan, int end, int x)
{
	int	start;

	start = 0;
	while (start < end)
	{
		mlx_put_pixel(_3d_plan, x, start, SKY);
		start++;
	}
}

void	floor_drawing(mlx_image_t *_3d_plan, int start, int x, t_color *color)
{
	static int	i;

	if (!(i % 5))
		swap_colors(&color[0], &color[1]);
	while (start < W_HEIGHT)
	{
		if ((int)start % 5)
			mlx_put_pixel(_3d_plan, x, start, color[0]);
		else
			mlx_put_pixel(_3d_plan, x, start, color[1]);
		start++;
	}
	i++;
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
	wall_height_reset(&y_inc, &end_y);
	while (y_inc < end_y)
	{
		idx.y = (y_inc - start_y) * (CS / w_height);
		mlx_put_pixel(data->_3d_map, i, y_inc, mtx[(int)idx.y][(int)idx.x]);
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
		wall_drawing(data, wall_height, i, data->tex_buf[4]);
	else if (ray.vert_hit && ray_direction(ray.angle, true) == LEFT)
		wall_drawing(data, wall_height, i, data->tex_buf[0]);
	else if (ray.vert_hit && ray_direction(ray.angle, true) == RIGHT)
		wall_drawing(data, wall_height, i, data->tex_buf[1]);
	else if (!ray.vert_hit && ray_direction(ray.angle, false) == UP)
		wall_drawing(data, wall_height, i, data->tex_buf[2]);
	else
		wall_drawing(data, wall_height, i, data->tex_buf[3]);
	wall_height_reset(&start_y, &end_y);
	sky_drawing(data->_3d_map, start_y, i);
	floor_drawing(data->_3d_map, end_y, i, (t_color [2]){BLACK, 0xc48a2eFF});
}

void	_3d_rendering_(t_cube *data)
{
	int		i;
	double	wall_height;
	double	distance_to_pp;

	i = 0;
	data->_3d_map = mlx_new_image(data->mlx, W_WIDHT, W_HEIGHT);
	distance_to_pp = (W_WIDHT / 2.0) / tan(data->player.fov / 2);
	while (i < W_WIDHT)
	{
		wall_height = CS * distance_to_pp / data->rays[i].distance;
		_slice_drawing(data, wall_height, i);
		i++;
	}
	mlx_image_to_window(data->mlx, data->_3d_map, 0, 0);
}

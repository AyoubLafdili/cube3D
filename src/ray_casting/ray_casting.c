/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:43:58 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/24 00:17:52 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	calc_distance(t_crd player, t_crd hit)
{
	return (sqrt(pow(hit.x - player.x, 2) + pow(hit.y - player.y, 2)));
}

t_direction	ray_direction(double ray_angle, bool horz_check)
{
	if (horz_check && ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)
		return (LEFT);
	else if (horz_check && (ray_angle > 3 * M_PI_2 || ray_angle < M_PI_2))
		return (RIGHT);
	if (ray_angle > M_PI && ray_angle < 2 * M_PI)
		return (UP);
	else
		return (DOWN);
}

bool    hit_check(t_cube *data, t_crd intersept, double angle, bool is_horz)
{
	int		y;
	int		x;

	if (is_horz && angle > M_PI && angle < 2 * M_PI)
			intersept.y--;
	else if (!is_horz && angle > M_PI_2 && angle < 3 * M_PI_2)
			intersept.x--;
	y = intersept.y / CS;
	x = intersept.x / CS;
	if (y < data->map.size && x < (int)data->map.longest
			&& is_wall(data->map._2d[y][x]))
			return (true);
	return (false);
}

void	save_ray_attr(t_crd player, t_crd horz, t_crd vert, t_ray *attr)
{
	double	h_d;
	double	v_d;

	h_d = calc_distance(player, horz);
	v_d = calc_distance(player, vert);
	if (h_d < v_d)
	{
		attr->distance = h_d;
		attr->hit_crd = horz;
		attr->vert_hit = false;
		return ;
	}
	attr->distance = v_d;
	attr->hit_crd = vert;
	attr->vert_hit = true;
}

void	cast_rays(t_cube *data)
{
	int		i;
	t_crd	horz;
	t_crd	vrtcl;
	double	ray_angle;

	i = 0;
	data->player.fov = 60 * M_PI / 180;
	ray_angle = data->player.rt_angel - (data->player.fov / 2);
	check_angel(&ray_angle);
	while (i < W_WIDHT)
	{
		check_angel(&ray_angle);
		horz = horz_intersect(data, data->player.crd, ray_angle);
		vrtcl = vert_intersect(data, data->player.crd, ray_angle);
		save_ray_attr(data->player.crd, horz, vrtcl, &data->rays[i]);
		data->rays[i].distance *= cos(ray_angle - data->player.rt_angel);
		data->rays[i].angle = ray_angle;
		ray_angle += (data->player.fov / W_WIDHT);
		i++;
	}
}

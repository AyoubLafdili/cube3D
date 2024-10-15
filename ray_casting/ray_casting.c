/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:43:58 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/15 22:10:00 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	hit_check(char **map, t_crd intersept, double angle, bool is_horz)
{
	int	y;
	int	x;

	if (is_horz && ray_direction(angle, false) == UP)
		intersept.y--;
	else if (!is_horz && ray_direction(angle, true) == LEFT)
		intersept.x--;
	y = intersept.y / CS;
	x = intersept.x / CS;
	if (y < 9 && x < 28 && (map[y][x] == '1'))
		return (1);
	if (y < 9 && x < 28 && map[y][x] == 'D')
		return (68);
	return (0);
}

void	save_ray_attr(t_cube *data, t_crd horz, t_crd vert, t_ray *attr)
{
	double		h_d;
	double		v_d;
	t_player	player;

	player = data->player;
	h_d = calc_distance(player.circle.center, horz);
	v_d = calc_distance(player.circle.center, vert);
	if (h_d < v_d)
	{
		attr->distance = h_d * cos(attr->angle - player.rt_angel);
		attr->door_hit = is_door_hit(data->map, horz, attr->angle, true);
		attr->vert_hit = false;
		attr->hit_crd = horz;
		return ;
	}
	attr->distance = v_d * cos (attr->angle - player.rt_angel);
	attr->door_hit = is_door_hit(data->map, vert, attr->angle, false);
	attr->vert_hit = true;
	attr->hit_crd = vert;
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
		data->rays[i].angle = ray_angle;
		horz = horz_intersect(data, data->player.circle.center, ray_angle);
		vrtcl = vert_intersect(data, data->player.circle.center, ray_angle);
		save_ray_attr(data, horz, vrtcl, &data->rays[i]);
		ray_angle += (data->player.fov / W_WIDHT);
		i++;
	}
}

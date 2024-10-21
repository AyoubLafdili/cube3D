/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_ray_casting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:32:24 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/21 22:35:34 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	door_hit_check(t_cube *data, t_crd *inter, double angle, bool is_horz)
{
	int	y;
	int	x;

	if (is_horz && ray_direction(angle, false) == UP)
		inter->y--;
	if (!is_horz && ray_direction(angle, true) == LEFT)
		inter->x--;
	y = inter->y / CS;
	x = inter->x / CS;
	if (y < 9 && x < 28 && data->map[y][x] == '1')
		return (1);
	if (y < 9 && x < 28 && data->map[y][x] == 'D')
		return (68);
	return (0);
}

bool	is_ray_door_hit(t_cube *data, t_crd *hit, double angle, bool is_horz)
{
	return ((door_hit_check(data, hit, angle, is_horz) >> 1 != 0) && (68 != 0));
}

t_crd	door_vert_inter(t_cube *data, t_crd start, double ray_angle)
{
	t_crd	intersept;
	t_crd	delta;

	intersept.x = floor(start.x / CS) * CS;
	if (ray_direction(ray_angle, true) == RIGHT)
		intersept.x += CS;
	intersept.y = start.y + ((intersept.x - start.x) * tan(ray_angle));
	delta.x = CS;
	if (ray_direction(ray_angle, true) == LEFT)
		delta.x = -delta.x;
	delta.y = delta.x * tan(ray_angle);
	if (ray_direction(ray_angle, false) == UP && delta.y > 0)
		delta.y = -delta.y;
	if (ray_direction(ray_angle, false) == DOWN && delta.y < 0)
		delta.y = -delta.y;
	while (intersept.x >= 0 && intersept.x < W_WIDHT
		&& intersept.y >= 0 && intersept.y < W_HEIGHT)
	{
		if (door_hit_check(data, &intersept, ray_angle, false))
			return (intersept);
		intersept.y += delta.y;
		intersept.x += delta.x;
	}
	return (intersept.x = __INT_MAX__, intersept.y = __INT_MAX__, intersept);
}

t_crd	door_horz_inter(t_cube *data, t_crd start, double ray_angle)
{
	t_crd	intersept;
	t_crd	delta;

	intersept.y = floor(start.y / CS) * CS;
	if (ray_direction(ray_angle, false) == DOWN)
		intersept.y += CS;
	intersept.x = start.x + ((intersept.y - start.y) / tan(ray_angle));
	delta.y = CS;
	if (ray_direction(ray_angle, false) == UP)
		delta.y = -delta.y;
	delta.x = delta.y / tan(ray_angle);
	if (ray_direction(ray_angle, true) == LEFT && delta.x > 0)
		delta.x = -delta.x;
	if (ray_direction(ray_angle, true) == RIGHT && delta.x < 0)
		delta.x = -delta.x;
	while (intersept.x >= 0 && intersept.x < W_WIDHT
		&& intersept.y >= 0 && intersept.y < W_HEIGHT)
	{
		if (door_hit_check(data, &intersept, ray_angle, true))
			return (intersept);
		intersept.y += delta.y;
		intersept.x += delta.x;
	}
	return (intersept.x = __INT_MAX__, intersept.y = __INT_MAX__, intersept);
}

void	cast_ray_door(t_cube *data, t_ray *r_door)
{
	t_crd	horz;
	t_crd	vert;
	double	distance[2];

	r_door->angle = data->player.rt_angel;
	horz = door_horz_inter(data, data->player.circle.center, r_door->angle);
	vert = door_vert_inter(data, data->player.circle.center, r_door->angle);
	distance[0] = calc_distance(data->player.circle.center, vert);
	distance[1] = calc_distance(data->player.circle.center, horz);
	if (distance[0] < distance[1])
	{
		r_door->distance = distance[0];
		r_door->vert_hit = true;
		r_door->hit_crd = vert;
		if (is_ray_door_hit(data, &r_door->hit_crd, r_door->angle, false))
			r_door->door_hit = true;
		return ;
	}
	r_door->distance = distance[1];
	r_door->vert_hit = false;
	r_door->hit_crd = horz;
	if (is_ray_door_hit(data, &r_door->hit_crd, r_door->angle, true))
		r_door->door_hit = true;
}

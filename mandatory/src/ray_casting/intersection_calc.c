/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_calc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:58:32 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/07 02:10:36 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_crd	vert_intersect(t_cube *data, t_crd start, double ray_angle)
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
	while (intersept.x >= 0 && intersept.x / CS < data->map.longest
		&& intersept.y >= 0 && intersept.y / CS < data->map.size)
	{
		if (hit_check(data, intersept, ray_angle, false))
			return (intersept);
		intersept.y += delta.y;
		intersept.x += delta.x;
	}
	return (intersept.x = __INT_MAX__, intersept.y = __INT_MAX__, intersept);
}

t_crd	horz_intersect(t_cube *data, t_crd start, double ray_angle)
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
	while (intersept.x >= 0 && intersept.x / CS < data->map.longest
		&& intersept.y >= 0 && intersept.y / CS < data->map.size)
	{
		if (hit_check(data, intersept, ray_angle, true))
			return (intersept);
		intersept.y += delta.y;
		intersept.x += delta.x;
	}
	return (intersept.x = __INT_MAX__, intersept.y = __INT_MAX__, intersept);
}

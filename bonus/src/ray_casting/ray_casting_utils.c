/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:15:34 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/28 15:43:08 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

t_door_lst	*get_rel_door(t_cube *data, t_crd ray)
{
	t_door_lst	*tmp;

	tmp = data->head;
	while (tmp)
	{
		if ((int)tmp->door.door_idxs.x == (int)ray.x / CS
			&& (int)tmp->door.door_idxs.y == (int)ray.y / CS)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	calc_offset(t_crd ray_hit, bool is_horz)
{
	if (is_horz)
		return ((int)ray_hit.x % CS);
	return ((int)ray_hit.y % CS);
}

double	calc_distance(t_crd player, t_crd hit)
{
	return (sqrt(pow(hit.x - player.x, 2) + pow(hit.y - player.y, 2)));
}

bool	is_dhit(t_cube *data, t_crd hit, double angle, bool is_horz)
{
	return ((hit_check(data, hit, angle, is_horz) >> 1 != 0) && (68 != 0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:05:04 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/08 18:57:35 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ft_sign(int nb)
{
	if (nb > 0)
		return (1);
	else if (nb < 0)
		return (-1);
	return (0);
}

void	ft_swap(double *x, double *y)
{
	double	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void	check_angel(double *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

void	wall_height_reset(int *_start_y, int *_end_y)
{
	if (*_start_y < 0)
		*_start_y = 0;
	if (*_end_y > W_HEIGHT)
		*_end_y = W_HEIGHT;
}

float	get_offset(t_cube *data, int ray_idx)
{
	t_door_lst	*door;
	t_ray		ray;

	ray = data->rays[ray_idx];
	door = get_rel_door(data, crd_dec(ray.hit_crd, ray.angle, !ray.vert_hit));
	if (!door)
		return (0);
	return (door->door.offset);
}

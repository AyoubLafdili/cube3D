/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:05:04 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/15 22:12:11 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	swap_colors(t_color *x, t_color *y)
{
	t_color	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void	wall_height_reset(int *_start_y, int *_end_y)
{
	if (*_start_y < 0)
		*_start_y = 0;
	if (*_end_y > W_HEIGHT)
		*_end_y = W_HEIGHT;
}

bool is_door_hit(char **map, t_crd hit, double angle, bool is_horz)
{
	return ((hit_check(map, hit, angle, is_horz) >> 1 != 0) && (68 != 0));
}

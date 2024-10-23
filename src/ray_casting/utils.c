/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:05:04 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/23 12:19:12 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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

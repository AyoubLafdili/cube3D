/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:05:04 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/25 15:36:35 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_sign(int nb)
{
	if (nb > 0)
		return (1);
	else if (nb < 0)
		return (-1);
	return (0);
}

void ft_swap(int *x, int *y)
{
	int tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;	
}

void check_angel(t_cube *data)
{
	if (data->player.rt_angel > 2 * M_PI)
		data->player.rt_angel = 0;
	if (data->player.rt_angel < 0)
		data->player.rt_angel = 2 * M_PI;
}

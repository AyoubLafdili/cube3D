/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:14:00 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/05 23:47:48 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

inline bool	is_zero(const char c)
{
	return (c == '0');
}

inline bool	is_wall(const char c)
{
	return (c == '1');
}

inline bool	is_door(const char c)
{
	return (c == 'D');
}

inline bool	valid_char(const char c)
{
	return (is_zero(c)
		|| is_wall(c)
		|| is_space(c)
		|| is_player(c)
		|| is_newline(c)
		|| is_door(c));
}

void	init_player(t_cube *data, int x, int y)
{
	if (is_north(data->map._2d[y][x]))
		data->player.rt_angle = 3 * M_PI_2;
	else if (is_south(data->map._2d[y][x]))
		data->player.rt_angle = M_PI_2;
	else if (is_east(data->map._2d[y][x]))
		data->player.rt_angle = 0;
	else if (is_west(data->map._2d[y][x]))
		data->player.rt_angle = M_PI;
	data->player.circle.center.x = x * CS + (CS / 2);
	data->player.circle.center.y = y * CS + (CS / 2);
	data->player.circle.radius = 2;
}

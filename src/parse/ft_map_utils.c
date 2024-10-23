/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:14:00 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/21 21:01:59 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

inline bool	is_zero(const char c)
{
	return (c == '0');
}

inline bool	is_wall(const char c)
{
	return (c == '1');
}

inline bool	is_map(const char c)
{
	return (is_space(c)
		|| is_wall(c)
		|| is_zero(c)
		|| is_player(c));
}

inline bool	is_player(const char c)
{
	return (is_east(c)
		|| is_north(c)
		|| is_south(c)
		|| is_west(c));
}

inline bool	valid_char(const char c)
{
	return (is_zero(c)
		|| is_wall(c)
		|| is_space(c)
		|| is_player(c)
		|| is_newline(c));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_psp_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:16:44 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/05 23:43:32 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

inline bool	is_east(const char c)
{
	return (c == 'E');
}

inline bool	is_north(const char c)
{
	return (c == 'N');
}

inline bool	is_south(const char c)
{
	return (c == 'S');
}

inline bool	is_west(const char c)
{
	return (c == 'W');
}

inline bool	is_player(const char c)
{
	return (is_east(c)
		|| is_north(c)
		|| is_south(c)
		|| is_west(c));
}

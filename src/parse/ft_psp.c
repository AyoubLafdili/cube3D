/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_psp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:16:44 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/21 21:09:18 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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

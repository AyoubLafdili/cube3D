/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:55:15 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/11 20:56:49 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline bool	is_space(const char c)
{
	return (c == ' ');
}

inline bool	is_newline(const char c)
{
	return (c == '\n');
}

inline bool	is_blank(const char *line)
{
	int				index;

	index = -1;
	while (line[++index])
	{
		if (!is_space(line[index]) && !is_newline(line[index]))
			return (false);
	}
	return (true);
}

inline bool	is_only(const char *line, const char c)
{
	int				index;

	if (!line || !c)
		return (true);
	index = -1;
	while (line[++index])
	{
		if (line[index] != c)
			return (false);
	}
	return (true);
}

long	ft_atol(const char *str)
{
	int				sign;
	long			result;

	sign = 1;
	result = 0;
	if (!str)
		return (-1);
	while (*str == 32)
		str++;
	if (*str == '-' && *str++)
		sign = -1;
	else if (*str == '+')
		str++;
	if (!ft_isdigit(*str) || !*str)
		return (LONG_MAX);
	while (ft_isdigit(*str))
	{
		result *= 10;
		result += (*str++ - '0');
		if (result > INT_MAX || result < INT_MIN)
			return (LONG_MAX);
	}
	if (!is_blank(str))
		return (-1);
	return (result * sign);
}

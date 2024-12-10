/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_it_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:56:01 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 21:44:49 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static char	*fill_row(char *row, int size)
{
	char			*filled;
	int				index;

	if (!row || size <= 0)
		return (NULL);
	index = -1;
	filled = ft_calloc(size, sizeof(char));
	if (filled == NULL)
		return (NULL);
	ft_memset(filled, ' ', size - 1);
	while (row[++index])
		filled[index] = row[index];
	return (filled);
}

int	square_it(t_map *map)
{
	char			**squared;
	int				row;

	row = -1;
	squared = ft_calloc(map->size + 1, sizeof(char *));
	if (squared == NULL)
		return (ft_error("malloc", "failed to allocate memory"));
	squared[map->size] = NULL;
	while (map->_2d[++row])
	{
		squared[row] = fill_row(map->_2d[row], map->longest);
		if (squared[row] == NULL)
			return (ft_clear_array(squared), ft_error("map", EAFTSI));
	}
	ft_clear_array(map->_2d);
	map->_2d = squared;
	return (SUCCESS);
}

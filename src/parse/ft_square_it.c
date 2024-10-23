/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_it.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:56:01 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/23 12:50:31 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static char	*fill_row(char *row, int size)
{
	char			*filled;
	int				index;

	if (!row || size <= 0)
		return (NULL);
	index = -1;
	filled = calloc(size, sizeof(char));
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
			return (ft_error("map", "failed to sqare it"));
		free(map->_2d[row]);
	}
	free(map->_2d);
	map->_2d = NULL;
	map->_2d = squared;
	return (SUCCESS);
}

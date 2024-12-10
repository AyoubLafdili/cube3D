/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:40:57 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 21:52:52 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static inline bool	in_bounds(t_map *map, int row, int col)
{
	return (col == 0
		|| col == (int)map->longest - 1
		|| row == 0
		|| row == map->size - 1);
}

static inline bool	inside(t_map *map, int row, int col, char c)
{
	if (is_space(c))
		return (is_space(map->_2d[row + 1][col])
			|| is_space(map->_2d[row - 1][col])
			|| is_space(map->_2d[row][col + 1])
			|| is_space(map->_2d[row][col - 1]));
	else
		return (((is_wall(map->_2d[row + 1][col])
				&& is_wall(map->_2d[row - 1][col])))
				|| ((is_wall(map->_2d[row][col + 1])
				&& is_wall(map->_2d[row][col - 1]))));
}

static int	has_alien(char *line)
{
	char			*alien;
	int				index;
	int				player;

	alien = NULL;
	index = -1;
	player = 0;
	while (line[++index])
	{
		if (is_player(line[index]))
			player++;
		if (line[ft_strlen(line) - 1] == '\n')
			return (ft_error("map", EMAPHNL));
		if (!valid_char(line[index]))
		{
			line[index + 1] = '\0';
			alien = line + index;
			return (ft_error(alien, EMAPHIC));
		}
	}
	if (player == 0)
		return (ft_error("player", EPNTFND));
	if (player > 1)
		return (ft_error("player", EPMLFND));
	return (SUCCESS);
}

static int	check_map(t_cube *cube)
{
	t_map			*map;
	int				row;
	int				col;

	map = &cube->map;
	row = -1;
	while (map->_2d[++row])
	{
		col = -1;
		while (++col < (int)map->longest)
		{
			if (is_player(map->_2d[row][col]))
				init_player(cube, col, row);
			if (is_zero(map->_2d[row][col])
				|| is_player(map->_2d[row][col])
				|| is_door(map->_2d[row][col]))
			{
				if (is_door(map->_2d[row][col]) && !inside(map, row, col, '1'))
					return (ft_maperror("door", row + 1, col + 1));
				if (in_bounds(map, row, col) || inside(map, row, col, ' '))
					return (ft_maperror("map", row + 1, col + 1));
			}
		}
	}
	return (SUCCESS);
}

int	ft_parse_map(t_cube *cube)
{
	if (!cube->map.content)
		return (ft_error("map", EMAPNTF));
	if (is_blank(cube->map.content))
		return (ft_error("map", EMAPHOS));
	if (cube->map.size < 3 || cube->map.longest < 3)
		return (ft_error("map", EMAPN33));
	if (has_alien(cube->map.content) != SUCCESS)
		return (FAILED);
	cube->map._2d = ft_split(cube->map.content, '\n');
	if (cube->map._2d == NULL)
		return (ft_error("map", "failed to split map"));
	if (square_it(&cube->map) != SUCCESS)
		return (FAILED);
	if (init_doors(cube))
		return (ft_error("malloc", "failed to alocate doors"));
	return (check_map(cube));
}

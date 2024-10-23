/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:24:57 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/23 23:17:01 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	check_duplicate_color(char *color)
{
	if (color[0] == 'C')
		return (ft_error(color, ECCAE));
	else if (color[0] == 'F')
		return (ft_error(color, ECFAE));
	return (SUCCESS);
}

static bool	has_alien(char **colors)
{
	int				row;
	int				col;

	row = -1;
	while (colors[++row])
	{
		col = -1;
		while (colors[row][++col])
		{
			if (!ft_isdigit(colors[row][col]) && !is_space(colors[row][col]))
				return (true);
		}
	}
	return (false);
}

static long	get_color(char **colors)
{
	uint32_t		r;
	uint32_t		g;
	uint32_t		b;

	r = ft_atol(colors[0]);
	g = ft_atol(colors[1]);
	b = ft_atol(colors[2]);
	if (!(r >= 0 && r <= UCHAR_MAX))
		return (ft_error(colors[0], ECOOR));
	else if (!(g >= 0 && g <= UCHAR_MAX))
		return (ft_error(colors[1], ECOOR));
	else if (!(b >= 0 && b <= UCHAR_MAX))
		return (ft_error(colors[2], ECOOR));
	return (r << 24 | g << 16 | b << 8 | 255);
}

static bool	is_valid_rgb(char *color)
{
	int				index;
	int				comma;
	bool			is_valid;

	if (!color)
		return (false);
	index = 0;
	comma = 0;
	is_valid = true;
	while (color[index])
	{
		if (ft_isdigit(color[index]) || (is_space(color[index])))
			;
		else if (color[index] == ',')
			comma++;
		else
			is_valid = false;
		index++;
	}
	if (!is_valid || comma != 2)
		return (false);
	return (true);
}

int	ft_parse_color(t_cube *cube, char *line)
{
	char			**colors;
	char			*color;
	size_t			size;
	bool			valid;
	long			shifted;

	line[ft_strlen(line) - 1] = '\0';
	color = line + 2;
	valid = is_valid_rgb(color);
	colors = ft_split(color, ',');
	size = ft_array_size(colors);
	if (!valid || !colors || size != 3 || has_alien(colors))
		return (ft_clear_array(colors, size), ft_error(line, ECNRGB));
	shifted = get_color(colors);
	if (shifted == FAILED)
		return (ft_clear_array(colors, size), FAILED);
	if (!ft_strncmp(line, "F ", 2) && cube->map.colors[F] == -1)
		cube->map.colors[F] = shifted;
	else if (!ft_strncmp(line, "C ", 2) && cube->map.colors[C] == -1)
		cube->map.colors[C] = shifted;
	else if (check_duplicate_color(line) != SUCCESS)
		return (ft_clear_array(colors, size), FAILED);
	return (ft_clear_array(colors, size), SUCCESS);
}

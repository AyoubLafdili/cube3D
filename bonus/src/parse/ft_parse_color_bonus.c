/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_color_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:24:57 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/11 21:10:26 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	if (r < 0 || r > UCHAR_MAX)
		return (ft_error(colors[0], ECOOR));
	g = ft_atol(colors[1]);
	if (g < 0 || g > UCHAR_MAX)
		return (ft_error(colors[1], ECOOR));
	b = ft_atol(colors[2]);
	if (b < 0 || b > UCHAR_MAX)
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
	bool			valid;
	long			shifted;

	line[ft_strlen(line) - 1] = '\0';
	color = line + 2;
	colors = NULL;
	valid = is_valid_rgb(color);
	if (valid)
		colors = ft_split(color, ',');
	if (!valid || !colors || has_alien(colors))
		return (ft_clear_array(colors), ft_error(line, ECNRGB));
	shifted = get_color(colors);
	if (shifted == FAILED)
		return (ft_clear_array(colors), FAILED);
	if (!ft_strncmp(line, "F ", 2) && cube->mt.colors[F] == -1)
		cube->mt.colors[F] = shifted;
	else if (!ft_strncmp(line, "C ", 2) && cube->mt.colors[C] == -1)
		cube->mt.colors[C] = shifted;
	else if (check_duplicate_color(line) != SUCCESS)
		return (ft_clear_array(colors), FAILED);
	return (ft_clear_array(colors), SUCCESS);
}

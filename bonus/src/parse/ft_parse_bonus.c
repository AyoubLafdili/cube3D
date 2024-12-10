/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:41:04 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/06 18:10:37 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	ft_readmap(t_cube *cube, char *line)
{
	char			*joined;

	joined = NULL;
	if (is_newline(*line) && !cube->map.content)
		return (SUCCESS);
	if (is_newline(*line))
		return (ft_error("map", EMAPHNL));
	if (cube->map.longest < (int)ft_strlen(line))
		cube->map.longest = ft_strlen(line);
	cube->map.size++;
	joined = ft_strjoin(cube->map.content, line);
	if (!joined)
		return (ft_error("join", "malloc failed!"));
	free(cube->map.content);
	cube->map.content = joined;
	return (SUCCESS);
}

int	ft_parse(t_cube *cube, char *line)
{
	if (!materials_inited(&cube->mt) && (is_newline(*line) || is_blank(line)))
		return (SUCCESS);
	if (is_texture(line))
		return (ft_parse_texture(cube, line));
	if (is_color(line))
		return (ft_parse_color(cube, line));
	if (materials_inited(&cube->mt))
		return (ft_readmap(cube, line));
	return (ft_error(line, "invalid line"));
}

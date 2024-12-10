/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_materials_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:35:11 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 02:10:36 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_texture(const char *line)
{
	if (!ft_strncmp(line, "NO ", 3)
		|| !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3)
		|| !ft_strncmp(line, "DO ", 3))
		return (true);
	return (false);
}

inline bool	is_color(const char *line)
{
	if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
		return (true);
	return (false);
}

bool	materials_inited(t_material *material)
{
	return (txtr_inited(material) == TXTRS_SZ
		&& colors_inited(material) == CLRS_SZ);
}

t_colors	colors_inited(t_material *material)
{
	if (material->colors[F] < 0)
		return (F);
	else if (material->colors[C] < 0)
		return (C);
	return (CLRS_SZ);
}

t_cardin	txtr_inited(t_material *material)
{
	if (!material->images[NO])
		return (NO);
	if (!material->images[EA])
		return (EA);
	if (!material->images[SO])
		return (SO);
	if (!material->images[WE])
		return (WE);
	return (TXTRS_SZ);
}

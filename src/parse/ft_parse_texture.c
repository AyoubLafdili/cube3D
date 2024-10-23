/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:34:21 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/23 20:19:47 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	check_duplicate_texture(const char *line)
{
	if (ft_strncmp(line, "NO", 2) == SUCCESS)
		return (ft_error("NO", ETXAE));
	else if (ft_strncmp(line, "EA", 2) == SUCCESS)
		return (ft_error("EA", ETXAE));
	else if (ft_strncmp(line, "SO", 2) == SUCCESS)
		return (ft_error("SO", ETXAE));
	else if (ft_strncmp(line, "WE", 2) == SUCCESS)
		return (ft_error("WE", ETXAE));
	return (SUCCESS);
}

static int	get_begining(char *line)
{
	int				index;

	index = 0;
	while (line[index])
	{
		if (line[index] != ' ')
			return (index);
		index++;
	}
	return (index);
}

static mlx_texture_t *ft_load_texture(char *str)
{
	mlx_texture_t	*texture;

	str += get_begining(str);
	str[ft_strlen(str) - 1] = '\0';
	texture = mlx_load_png(str);
	if (texture == NULL)
		return (NULL);
	return (texture);
}

int	ft_parse_texture(t_cube *cube, char *line)
{
	mlx_texture_t		*mtexture;
	char				*texture;

	texture = line + 3;
	mtexture = ft_load_texture(texture);
	if (!mtexture)
		return (ft_error(line, EIFAIL));
	if (!ft_strncmp(line, "NO", 2) && !cube->map.textures[NO])
		cube->map.textures[NO] = mtexture;
	else if (!ft_strncmp(line, "EA", 2) && !cube->map.textures[EA])
		cube->map.textures[EA] = mtexture;
	else if (!ft_strncmp(line, "SO", 2) && !cube->map.textures[SO])
		cube->map.textures[SO] = mtexture;
	else if (!ft_strncmp(line, "WE", 2) && !cube->map.textures[WE])
		cube->map.textures[WE] = mtexture;
	else if (check_duplicate_texture(line) != SUCCESS)
		return (FAILED);
	return (SUCCESS);
}

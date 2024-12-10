/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_texture_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:34:21 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/08 18:59:08 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
	else if (ft_strncmp(line, "DO", 2) == SUCCESS)
		return (ft_error("DO", ETXAE));
	return (SUCCESS);
}

static int	get_begining(const char *line)
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

static mlx_image_t	*ft_load_image(mlx_t *mlx, char *str)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	int				fd;

	str += get_begining(str);
	str[ft_strlen(str) - 1] = '\0';
	fd = open(str, O_RDONLY);
	if (fd == FAILED)
		return (NULL);
	close(fd);
	texture = mlx_load_png(str);
	if (texture == NULL)
		return (NULL);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (image == NULL)
		return (NULL);
	return (image);
}

int	ft_parse_texture(t_cube *cube, char *line)
{
	mlx_image_t			*img;
	char				*texture;

	texture = line + 3;
	img = ft_load_image(cube->mlx, texture);
	if (!img || !mlx_resize_image(img, CS, CS))
		return (ft_error(line, EIFAIL));
	if (!ft_strncmp(line, "NO", 2) && !cube->mt.images[NO])
		cube->mt.images[NO] = img;
	else if (!ft_strncmp(line, "EA", 2) && !cube->mt.images[EA])
		cube->mt.images[EA] = img;
	else if (!ft_strncmp(line, "SO", 2) && !cube->mt.images[SO])
		cube->mt.images[SO] = img;
	else if (!ft_strncmp(line, "WE", 2) && !cube->mt.images[WE])
		cube->mt.images[WE] = img;
	else if (!ft_strncmp(line, "DO", 2) && !cube->mt.images[DO])
		cube->mt.images[DO] = img;
	else if (check_duplicate_texture(line) != SUCCESS)
		return (FAILED);
	return (SUCCESS);
}

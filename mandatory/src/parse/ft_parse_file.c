/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:03:49 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 02:10:36 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	get_pixel(uint8_t *channel)
{
	uint32_t	color;

	color = 0;
	color |= channel[0] << 24;
	color |= channel[1] << 16;
	color |= channel[2] << 8;
	color |= channel[3];
	return (color);
}

void	textures_init(t_material *mt)
{
	int				i;
	uint32_t		j;
	uint32_t		x;
	int				y;

	i = -1;
	while (++i < TXTRS_SZ)
	{
		y = 0;
		j = 0;
		while (j < CS * CS * TXTRS_SZ)
		{
			x = 0;
			while (x < mt->images[i]->width)
			{
				mt->tex_buf[i][y][x] = get_pixel(&mt->images[i]->pixels[j]);
				j += 4;
				x++;
			}
			y++;
		}
	}
}

int	ft_readfile(int fd, int parse(t_cube *, char *), t_cube *cube)
{
	char			*line;
	bool			status;

	line = NULL;
	status = false;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			if (status == false)
				return (EFEMPTY);
			break ;
		}
		if (status == false)
			status = true;
		if (parse(cube, line) != SUCCESS)
			return (free(line), FAILED);
		free(line);
	}
	if (!materials_inited(&cube->mt))
		return (ft_error("materials", "missed material"));
	textures_init(&cube->mt);
	return (ft_parse_map(cube));
}

int	parse_file(t_cube *cube, char *filename)
{
	int				fd;
	int				status;

	fd = open(filename, O_RDONLY);
	if (fd == FAILED)
		return (ft_error(filename, NULL));
	status = ft_readfile(fd, ft_parse, cube);
	free(cube->map.content);
	del_prev(cube, txtr_inited(&cube->mt));
	close(fd);
	if (status == FAILED)
		return (FAILED);
	if (status == EFEMPTY)
		return (ft_error(filename, EMFEMPTY));
	return (SUCCESS);
}

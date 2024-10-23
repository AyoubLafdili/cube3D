/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:03:49 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/23 20:48:56 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

uint32_t	get_pixel_color(uint8_t *channel)
{
	uint32_t	color;

	color = 0;
	color |= channel[0] << 24;
	color |= channel[1] << 16;
	color |= channel[2] << 8;
	color |= channel[3];
	return (color);
}

void	textures_init(mlx_texture_t	*texture, uint32_t mtx[CS][CS])
{
	uint32_t		i;
	uint32_t		x;
	int				y;

	i = 0;
	y = i;
	while (i < CS * CS * texture->bytes_per_pixel)
	{
		x = 0;
		while (x < texture->width)
		{
			mtx[y][x] = get_pixel_color(&texture->pixels[i]);
			i += texture->bytes_per_pixel;
			x++;
		}
		y++;
	}
	// mlx_delete_texture(texture);
}

static int	check_file_status(char *filename, int status)
{
	if (status == EISDIR)
		return (ft_error(filename, strerror(EISDIR)));
	if (status == ENOENT)
		return (ft_error(filename, strerror(ENOENT)));
	if (status == EFEMPTY)
		return (ft_error(filename, "File is empty"));
	// if (status == EMHASTAB)
	// 	return (ft_error(filename, "Map has tab"));
	return (SUCCESS);
}

int	ft_readfile(int fd, int parse(t_cube *, char *), t_cube *cube)
{
	char			*line;
	bool			status;

	line = NULL;
	status = false;
	cube->map.point = (t_point){0};
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			if (status == false)
				return (EFEMPTY);
			break ;
		}
		cube->map.point.row++;
		if (parse(cube, line) != SUCCESS)
			return (free(line), FAILED);
		free(line);
		status = true;
	}
	if (!materials_inited(&cube->map))
		return (ft_error("materials", "missed material"));
	textures_init(cube->map.textures[NO], cube->tex_buf[NO]);
	textures_init(cube->map.textures[SO], cube->tex_buf[SO]);
	textures_init(cube->map.textures[EA], cube->tex_buf[EA]);
	textures_init(cube->map.textures[WE], cube->tex_buf[WE]);
	return (ft_parse_map(cube));
}

int	parse_file(t_cube *cube, char *filename)
{
	int				fd;
	int				index;
	int				status;

	fd = open(filename, O_RDONLY);
	if (fd == FAILED)
		return (ft_error(filename, NULL));
	status = ft_readfile(fd, ft_parse, cube);
	index = 0;
	while (index < TXTRS_SZ && cube->map.textures[index])
		mlx_delete_texture(cube->map.textures[index++]);
	if (status == FAILED)
		return (close(fd), FAILED);
	return (close(fd), check_file_status(filename, status));
}

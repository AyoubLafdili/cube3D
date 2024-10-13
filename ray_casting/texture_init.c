/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:13 by alafdili          #+#    #+#             */
/*   Updated: 2024/10/13 18:30:16 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	textures_init(char *path, uint32_t mtx[CS][CS])
{
	mlx_texture_t	*texture;
	uint32_t		i;
	uint32_t		x;
	int				y;

	i = 0;
	y = i;
	texture = mlx_load_png(path);
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
	mlx_delete_texture(texture);
}

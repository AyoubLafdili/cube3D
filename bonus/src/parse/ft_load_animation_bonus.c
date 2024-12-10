/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_animation_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:16:30 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 21:46:07 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static char	*get_path(int index)
{
	char			*relative;
	char			*path;
	char			*number;

	number = ft_itoa(index);
	if (!number)
		return (ft_error("itoa", "failed to convert integer to int"), NULL);
	path = ft_strjoin("textures/sprite/", number);
	free(number);
	if (!path)
		return (ft_error("strjoin", "failed to join path with name"), NULL);
	relative = ft_strjoin(path, ".png");
	free(path);
	if (!relative)
		return (ft_error("strjoin", "failed to join path with .png ext"), NULL);
	return (relative);
}

int	load_sprite(t_cube *cube)
{
	mlx_texture_t	*tex;
	char			*path;
	int				index;

	index = 0;
	while (index < 46)
	{
		path = get_path(index);
		if (!path)
			return (FAILED);
		tex = mlx_load_png(path);
		free(path);
		if (!tex)
			return (ft_error("sprite", "error load sprite as texture"));
		cube->mt.sprites[index] = mlx_texture_to_image(cube->mlx, tex);
		mlx_delete_texture(tex);
		if (cube->mt.sprites[index] == NULL)
			return (ft_error("mlx", "failed to convert texture to image"));
		cube->mt.sp_size++;
		if (!mlx_resize_image(cube->mt.sprites[index], 1080, 720))
			return (ft_error("mlx", "failed to resize image"));
		index++;
	}
	return (SUCCESS);
}

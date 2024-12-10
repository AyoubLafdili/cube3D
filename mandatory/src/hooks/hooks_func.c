/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:59:06 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/04 22:34:22 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_callback(void *param)
{
	t_cube	*data;

	data = (t_cube *)param;
	mlx_delete_image(data->mlx, data->mt._3d_map);
	destroy_game(data, EXIT_SUCCESS);
}

void	rerendere_map(void *param)
{
	t_cube	*data;

	data = param;
	cast_rays(data);
	if (_3d_rendering_(data) == FAILED)
		destroy_game(data, EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:51:38 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 02:07:15 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	mouse_moves(double xpos, double ypos, void *param)
{
	t_cube			*cube;
	static int		last_x;

	cube = (t_cube *)param;
	if (cube->mini.sh_exp || ypos < 0 || ypos > W_HEIGHT)
		return ;
	if (xpos < 0)
		mlx_set_mouse_pos(cube->mlx, W_WIDHT, ypos);
	else if (xpos > W_WIDHT)
		mlx_set_mouse_pos(cube->mlx, 0, ypos);
	if (fabs(xpos - last_x) > DEAD_ZONE)
	{
		if (last_x < xpos)
			mv_hdlr(cube, T_RIGHT);
		else if (last_x > xpos)
			mv_hdlr(cube, T_LEFT);
		last_x = xpos;
	}
}

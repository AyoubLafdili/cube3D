/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:57:26 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/17 14:57:26 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "MLX42.h"

# define FAIL 1
# define SUCSESS 0
#define WINDOW_HEIGHT 60 * 9
#define WINDOW_WIDHT 60 * 7

typedef struct s_player
{
    int px;
    int py;
    int cx;
    int cy;
    int radius;
    int rt_angel;
}t_player;

typedef struct s_cube
{
    char **map;
    t_player player;
    mlx_image_t *map_i;
    mlx_t *mlx;
}t_cube;
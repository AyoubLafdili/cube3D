/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 03:30:13 by W2Wizard          #+#    #+#             */
/*   Updated: 2024/10/01 11:17:05 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

// BUG: Linux may experience a red hue instead due to endianness
void mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

//= Public =//

void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	MLX_NONNULL(image);
	MLX_ASSERT(x < image->width, "Pixel is out of bounds");
	MLX_ASSERT(y < image->height, "Pixel is out of bounds");

	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];
	mlx_draw_pixel(pixelstart, color);
}

#include "cub3d.h"

void symmetry_pixels(mlx_image_t *image, int y, int x)
{
	int cx;
	int cy;

	cx = 200 / 2;
	cy = 200 / 2;
    printf("cx = %d\t| cy = %d | x = %d\t| y = %d\n", cx, cy, x, y);
	// mlx_put_pixel(image, y, x, red);

	mlx_put_pixel(image, cx + x, cy + y, RED);
	mlx_put_pixel(image, cx + y, cy - x, RED);
	mlx_put_pixel(image, cx + y, cy + x, RED);
	mlx_put_pixel(image, cx + x, cy - y, RED);
	mlx_put_pixel(image, cx - x, cy - y, RED);
	mlx_put_pixel(image, cx - y, cy - x, RED);
	mlx_put_pixel(image, cx - y, cy + x, RED);
	mlx_put_pixel(image, cx - x, cy + y, RED);
}

void draw_circle(mlx_image_t *image, int cx, int cy)
{
    int x;
	int y;
	int param;

	x = 0;
	y = 10;
	param = 1 - 10;
    mlx_put_pixel(image, cx, cy, BLACK);
    symmetry_pixels(image, y, x);
	while (x < y)
	{
		if (param < 0)
		{
			param = param + (2 * x) + 3;
			x += 1;
			symmetry_pixels(image, y, x);
		}
		else
		{
			param = param + (2 * (x - y)) + 5;
			x += 1;
			y -= 1;
			symmetry_pixels(image, y, x);
		}
	}

}

int main ()
{
    mlx_t *mlx;
    mlx_image_t *image;
    int cx, cy;

    cx = 200 / 2;
    cy = 200 / 2;
    mlx = mlx_init(300, 300, "test", 1);
    if (!mlx)
        ft_putendl_fd("mlx_init", 2);
    image = mlx_new_image(mlx, 300, 300);
    if (!image)
        ft_putendl_fd("mlx_new_image", 2);
    for (int y = 0; y < 300; y++)
        for (int x = 0; x < 300; x++)
            mlx_put_pixel(image, x, y, WHITE);
    draw_circle(image, cx, cy);
    mlx_image_to_window(mlx, image, 0, 0);
    mlx_loop(mlx);
}

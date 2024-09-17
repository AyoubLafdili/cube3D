#include "cube3d.h"

void draw_triangle(mlx_image_t *image)
{
    int y;
    int l;
    int r;
    int x;

    y = 20;
    r = l = 30;

    while (y < 30)
    {
        x = 0;
        while (x < 60)
        {
            if (x >= l && x <= r)
                mlx_put_pixel(image, x, y, 0xFF0000FF);
            x++;
        }
        l -= 1;
        r += 1;
        y++;
    }
}

int main ()
{
    int y;
    int x;
    mlx_t *mlx;
    mlx_image_t *image;

    mlx = mlx_init(500, 500, "test", 0);
    if (!mlx)
        ft_putendl_fd("mlx_init", 2);
    mlx_texture_t *texture = mlx_load_png("../white.png");
    image = mlx_texture_to_image(mlx, texture);
    if (!image)
        ft_putendl_fd("mlx_new_image", 2);
    mlx_image_to_window(mlx, image, 0, 0);
    draw_triangle(image);
    mlx_loop(mlx);
}

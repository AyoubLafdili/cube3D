#include "cube3d.h"

void draw_triangle(mlx_image_t *image)
{
    int y;
    int l;
    int r;
    int x;

    y = 20;
    r = l = 30;
    while (y < BOX / 2)
    {
        x = 0;
        while (x < BOX)
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

void draw_images(t_cube *data)
{
    int x;
    int y;
    mlx_t *mlx;

    y = x = 0;
    mlx = data->mlx;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == '0')
                if (mlx_image_to_window(mlx, data->space_i, x * BOX, y * BOX) == -1)
                    ft_putendl_fd("image_to_window", 2);
            if (data->map[y][x] == '1')
                if (mlx_image_to_window(mlx, data->wall_i, x * BOX, y * BOX) == -1)
                    ft_putendl_fd("image_to_window", 2);
            if (data->map[y][x] == 'P')
            {
                data->player.px = x;
                data->player.py = y;
                if (mlx_image_to_window(mlx, data->player_i, x * BOX, y * BOX) == -1)
                    ft_putendl_fd("image_to_window", 2);
            }
            x++;
        }
        y++;
    }
}

int init_images(t_cube *data)
{    
    data->texture = mlx_load_png(WHITE);
    if (!data->texture)
        return (ft_putendl_fd("mlx_load_png", 2), FAIL);
    data->space_i = mlx_texture_to_image(data->mlx, data->texture);
    if (!data->space_i)
    {
        mlx_delete_texture(data->texture);
        return (ft_putendl_fd("mlx_texture_to_image", 2), FAIL);
    }
    mlx_delete_texture(data->texture);
    data->texture = mlx_load_png(BLACK);
    if (!data->texture)
        return (ft_putendl_fd("mlx_load_png", 2), FAIL);
    data->wall_i = mlx_texture_to_image(data->mlx, data->texture);
    if (!data->wall_i)
    {
        mlx_delete_texture(data->texture);
           return (ft_putendl_fd("mlx_texture_to_image", 2), FAIL);
    }
    mlx_delete_texture(data->texture);
    data->texture = mlx_load_png(WHITE);
    if (!data->texture)
        return (ft_putendl_fd("mlx_load_png", 2), FAIL);
    data->player_i = mlx_texture_to_image(data->mlx, data->texture);
    if (!data->player_i)
        return (ft_putendl_fd("mlx_texture_to_image", 2), FAIL);
    return (0);
}

int main()
{
    t_cube data;
    char *map[] = { 
        "1111111",
        "1000101",
        "1000101",
        "1010001",
        "1010001",
        "1000001",
        "1001001",
        "10000P1",
        "1111111",
        NULL
        };
    ft_memset(&data, 0, sizeof(t_cube));
    data.map = map;
    data.player.rt_angel = M_PI / 2;
    data.mlx = mlx_init(BOX * 7, BOX * 9, "cube3d", 0);
    if (!data.mlx)
       printf("mlx_init");
    init_images(&data);
    draw_triangle(data.player_i);
    draw_images(&data);
    mlx_loop(data.mlx);
    return (0);
}
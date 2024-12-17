#include "cub3d_parse.h"

void	clear_canvas(t_data *stuff)
{
	if (stuff->game_img.img)
		mlx_destroy_image(stuff->mlx, stuff->game_img.img);
	mlx_clear_window(stuff->mlx, stuff->window);
	stuff->game_img.img = mlx_new_image(stuff->mlx, WIDTH, HEIGHT);
	if (!stuff->game_img.img)
		exit(1);
	stuff->game_img.addr = (char *)mlx_get_data_addr(stuff->game_img.img, \
		&stuff->game_img.bits_per_pixel, \
		&stuff->game_img.line_length, &stuff->game_img.endian);
	if (!stuff->game_img.addr)
		exit(1);
	stuff->game_img.pixs = (int *)stuff->game_img.addr;
}

int	game_loop(void *arg)
{
	t_data	*stuff;

	stuff = arg;
	clear_canvas(stuff);
	do_stuff(stuff);
	ray_shit(stuff);
	mlx_put_image_to_window(stuff->mlx, stuff->window, stuff->game_img.img, 0, 0);


	return (0);
}
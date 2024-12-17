#include "cub3d_parse.h"

int	init_tex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		printf("{%s}  \n",((char **)data->textures)[i]);
		if (!i || i == 2)
			data->textures->texs[i].xpm.img = mlx_xpm_file_to_image(data->mlx, \
			"textures/wolfenstein/grey_stone.xpm", &data->textures->texs[i].w, &data->textures->texs[i].h);
		else
			data->textures->texs[i].xpm.img = mlx_xpm_file_to_image(data->mlx, \
			"textures/wolfenstein/mossy.xpm", &data->textures->texs[i].w, &data->textures->texs[i].h);
		if (!data->textures->texs[i].xpm.img)
			return (1);
		data->textures->texs[i].xpm.pixs = (int *)mlx_get_data_addr(data->textures->texs[i].\
		xpm.img, &data->textures->texs[i].xpm.bits_per_pixel, \
			&data->textures->texs[i].xpm.line_length, &data->textures->texs[i].xpm.endian);
		if (!data->textures->texs[i].xpm.pixs)
			return (1);
		data->textures->texs[i].xpm.addr = (char *)data->textures->texs[i].xpm.pixs;
	}
	return (0);
}

int	init_data(t_data *data)
{
	// mlx 
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3p");
	if (!data->window)
		return (1);
	data->game_img.img = NULL;

	// data->coords.player.x += 0.5;
	// data->coords.player.y += 0.5;
	data->mov_sped = 0.1;
	data->rot_sped = 0.1;
	if (data->coords.player.pos == north)// north side
	{	data->coords.player.dir.x = 0;
		data->coords.player.dir.y = -1;
		data->coords.player.plane.x = -0.66;
		data->coords.player.plane.y = 0;
	}
	if (data->coords.player.pos == south)// south 
	{
		data->coords.player.dir.x = 0;
		data->coords.player.dir.y = 1;
		data->coords.player.plane.x = 0.66;
		data->coords.player.plane.y = 0;
	}
	if (data->coords.player.pos == east)// east
	{
		data->coords.player.dir.x = 1;
		data->coords.player.dir.y = 0;
		data->coords.player.plane.x = 0;
		data->coords.player.plane.y = -0.66;
	}
	if (data->coords.player.pos == west)// KANYE???
	{
		data->coords.player.dir.x = 1;
		data->coords.player.dir.y = 0;
		data->coords.player.plane.x = 0;
		data->coords.player.plane.y = -0.66;
	}
	return (init_tex(data));
}

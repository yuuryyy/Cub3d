/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:09:10 by achbira           #+#    #+#             */
/*   Updated: 2025/04/25 18:15:07 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	clear_canvas(t_data *data)
{
	if (data->game_img.img)
		mlx_destroy_image(data->mlx, data->game_img.img);
	data->game_img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->game_img.img)
		return (error("Failed to create image."), 1);
	data->game_img.addr = mlx_get_data_addr(data->game_img.img, \
		&data->game_img.bits_per_pixel, \
		&data->game_img.line_length, &data->game_img.endian);
	if (!data->game_img.addr)
		return (error("Failed to get image data."), 1);
	return (0);
}

int	game_loop(void *arg)
{
	t_data	*data;

	data = arg;
	if (clear_canvas(data))
		x_exit(data);
	data->sprite_idx += 0.3;
	if (data->sprite_idx > 10)
		data->sprite_idx = 0;
	move_player(data);
	create_world(data);
	draw_minimap(data);
	if (data->coords.player.target_door.x != -1)
	{
		t_loaded_tex tex = data->e_tex;
		int i = 0;
		int j = 0;
		while (i < tex.height)
		{
			j = 0;
			while (j < tex.width)
			{
				int color = ((int *)tex.img.addr)[i * tex.width + j];
				// if (get_dist(HEIGHT/2 , WIDTH/2, HEIGHT / 2 - tex.height/2 + i, WIDTH /2 - tex.width/2 + j) > tex.width / 2)
					// continue;
				// else
					pp(WIDTH /2 - tex.width/2 + j, HEIGHT / 2 - tex.height/2 + i, color, &data->game_img);
				j++;
			}
			i++;
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->game_img.img, 0, 0);
	return (0);
}

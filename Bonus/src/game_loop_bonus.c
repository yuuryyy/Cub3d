/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:09:10 by achbira           #+#    #+#             */
/*   Updated: 2025/04/25 21:28:41 by achbira          ###   ########.fr       */
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

void	put_button(t_data *data, t_loaded_tex tex)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < tex.height)
	{
		j = 0;
		while (j < tex.width)
		{
			color = ((int *)tex.img.addr)[i * tex.width + j];
			if (get_dist(j, i, tex.width / 2, tex.height / 2) \
				> tex.width / 2 && ++j)
				continue ;
			else
				pp(WIDTH / 2 - tex.width / 2 + j, 3 * HEIGHT / 4 \
					- tex.height / 2 + i, color, &data->game_img);
			j++;
		}
		i++;
	}
}

int	game_loop(void *arg)
{
	t_data		*data;
	t_player	p;

	data = arg;
	p = data->coords.player;
	if (clear_canvas(data))
		x_exit(data);
	data->sprite_idx += 0.5;
	if (data->sprite_idx > 18)
		data->sprite_idx = 0;
	move_player(data);
	create_world(data);
	draw_minimap(data);
	if (p.target_door.x != -1 \
		&& get_dist(p.x, p.y, p.target_door.x, p.target_door.y) < 2)
		put_button(data, data->e_tex);
	mlx_put_image_to_window(data->mlx, data->window, data->game_img.img, 0, 0);
	return (0);
}

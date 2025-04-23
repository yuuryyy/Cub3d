/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:09:10 by achbira           #+#    #+#             */
/*   Updated: 2025/04/23 17:40:10 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

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
	
	move_player(data);
	
	create_world(data);
	mlx_put_image_to_window(data->mlx, data->window, data->game_img.img, 0, 0);
	
	return (0);
}

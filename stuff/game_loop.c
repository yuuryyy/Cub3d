/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:09:10 by achbira           #+#    #+#             */
/*   Updated: 2025/03/16 00:37:23 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	clear_canvas(t_data *data)
{
	if (data->game_img.img)
		mlx_destroy_image(data->mlx, data->game_img.img);
	data->game_img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->game_img.img)
		exit(1);//TODO error msg 
	data->game_img.addr = mlx_get_data_addr(data->game_img.img, \
		&data->game_img.bits_per_pixel, \
		&data->game_img.line_length, &data->game_img.endian);
	if (!data->game_img.addr)
		exit(1);//TODO error msg 
}

int	game_loop(void *arg)
{
	t_data	*data;

	data = arg; // TODO (t_data *)arg 
	clear_canvas(data);
	
	move_player(data);
	
	create_world(data);
	mlx_put_image_to_window(data->mlx, data->window, data->game_img.img, 0, 0);


	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:40 by achbira           #+#    #+#             */
/*   Updated: 2025/04/25 21:14:24 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	x_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	free_data(data);
	return (exit(0), 0);
}

void	close_open_door(t_data *data, t_vect door, t_player p)
{
	if (door.x != -1 && get_dist(p.x, p.y, door.x, door.y) < 2)
	{
		if (data->map[(int)door.y][(int)door.x] == '2')
			data->map[(int)door.y][(int)door.x] = '3';
		else
			data->map[(int)door.y][(int)door.x] = '2';
	}
}

int	key_press_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		return (x_exit(data));
	if (keycode == 'w')
		data->move.w = 1;
	if (keycode == 's')
		data->move.s = 1;
	if (keycode == 65363)
		data->move.rr = 1;
	if (keycode == 65361)
		data->move.rl = 1;
	if (keycode == 'a')
		data->move.a = 1;
	if (keycode == 'd')
		data->move.d = 1;
	if (keycode == 'q')
		data->move.mov_sped *= 2;
	if (keycode == 'e')
		close_open_door(data, data->coords.player.target_door, \
			data->coords.player);
	return (0);
}

int	key_release_hook(int keycode, t_data *data)
{
	if (keycode == 'w')
		data->move.w = 0;
	if (keycode == 's')
		data->move.s = 0;
	if (keycode == 65363)
		data->move.rr = 0;
	if (keycode == 65361)
		data->move.rl = 0;
	if (keycode == 'a')
		data->move.a = 0;
	if (keycode == 'd')
		data->move.d = 0;
	if (keycode == 'q')
		data->move.mov_sped /= 2;
	return (0);
}

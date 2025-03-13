/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:40 by achbira           #+#    #+#             */
/*   Updated: 2025/03/13 20:34:41 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

int	esc_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	free_data(data);
	return (exit (0), 0);
}

int	x_exit(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	free_data(data);
	return (exit (0), 0);
}

int	key_press_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		return (esc_exit(data));
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
	return (0);
}

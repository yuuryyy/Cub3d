/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:52:08 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/17 02:37:32 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	use_hips2(float angle, t_player *p)
{
	float oldx = p->dir.x;

	p->dir.x = p->dir.x * cos(angle) - p->dir.y *sin(angle);
	p->dir.y = oldx * sin(angle) + p->dir.y *cos(angle);
	oldx = p->plane.x;
	p->plane.x = p->plane.x * cos(angle) - p->plane.y *sin(angle);
	p->plane.y = oldx * sin(angle) + p->plane.y *cos(angle);
}

int	mouse_rot(int x, int y, void *arg)
{
	t_data	*data;
	static int	a;

	data = arg;
	if (a < x)
		use_hips2(data->rot_sped, &data->coords.player);
	else
		use_hips2(-data->rot_sped, &data->coords.player);
	return (a = x);
}

int main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ac != 2)
		return (error(ARGNUM), 1);
	if(check_data(&data, av))
		return (1);
	if (init_data(&data))
		return (free_data(&data), 1);
	mlx_hook(data.window, 6, 0, mouse_rot, &data);
	mlx_hook(data.window, 2, 0, hook_press, &data);
	mlx_hook(data.window, 3, 0, hook_release, &data);
	mlx_hook(data.window, 17, 0, x_close, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	free_data(&data);
}

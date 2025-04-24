/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:52:08 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/24 16:09:02 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

	y += 0;
	data = arg;
	if (a < x)
		use_hips2(data->move.rot_sped/2, &data->coords.player);
	else
		use_hips2(-data->move.rot_sped/2, &data->coords.player);
	if (x > WIDTH - 200 || x < 200)
		mlx_mouse_move(data->mlx, data->window, WIDTH / 2, y);
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


	mlx_mouse_hide(data.mlx, data.window);
	mlx_hook(data.window, 6, (1L<<6), mouse_rot, &data);
	mlx_hook(data.window, 2, (1L<<0), key_press_hook, &data);
	mlx_hook(data.window, 3, (1L<<1), key_release_hook, &data);
	mlx_hook(data.window, 17, (1L<<17), x_exit, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	free_data(&data);
}

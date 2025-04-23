/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:52:08 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/15 11:48:27 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

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


	mlx_hook(data.window, 2, (1L<<0), key_press_hook, &data);
	mlx_hook(data.window, 3, (1L<<1), key_release_hook, &data);
	mlx_hook(data.window, 17, (1L<<17), x_exit, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	free_data(&data);
}

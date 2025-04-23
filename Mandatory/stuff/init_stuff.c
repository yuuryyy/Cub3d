/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:37 by achbira           #+#    #+#             */
/*   Updated: 2025/04/15 11:34:20 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

int	direct_player(t_player *joueur)
{
	joueur->x += 0.5;
	joueur->y += 0.5;

	joueur->dir.x = (joueur->pos == east) - (joueur->pos == west);
	joueur->dir.y = (joueur->pos == south) - (joueur->pos == north);

	joueur->plane.x = 0.66 * (joueur->pos == north) - (joueur->pos == south);
	joueur->plane.y = 0.66 * (joueur->pos == east) - (joueur->pos == west);
	return (0);
}

int	init_data(t_data *data)
{
	// mlx 
	data->mlx = mlx_init();
	if (!data->mlx)
		return (error("Failed to set up mlx connection."), 1);
	load_all_textures(&data->ready_tex, data->mlx, data);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "arson is cool");
	if (!data->window)
		return (error("Failed to create window."), 1);
	data->game_img.img = NULL; // TODO: bzero would be better todo
	
	data->move.mov_sped = BASE_SPEED;
	data->move.rot_sped = BASE_ROTATION_SPEED;
	direct_player(&data->coords.player);
	return (0);
}

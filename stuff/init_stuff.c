/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:37 by achbira           #+#    #+#             */
/*   Updated: 2025/03/13 20:34:38 by achbira          ###   ########.fr       */
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


	// if (joueur->pos == north)// north side
	// {	joueur->dir_x = 0;
	// 	joueur->dir_y = -1;
	// 	joueur->plane.x = 0.66;
	// 	joueur->plane.y = 0;
	// }
	// if (joueur->pos == south)// south 
	// {
	// 	joueur->dir_x = 0;
	// 	joueur->dir_y = 1;
	// 	joueur->plane.x = -0.66;
	// 	joueur->plane.y = 0;
	// }
	// if (joueur->pos == east)// east
	// {
	// 	joueur->dir_x = 1;
	// 	joueur->dir_y = 0;
	// 	joueur->plane.x = 0;
	// 	joueur->plane.y = 0.66;
	// }
	// if (joueur->pos == west)// KANYE??? miss westieee
	// {
	// 	joueur->dir_x = -1;
	// 	joueur->dir_y = 0;
	// 	joueur->plane.x = 0;
	// 	joueur->plane.y = -0.66;
	// }
	return (0);
}


int	init_data(t_data *data)
{
	
	// mlx 
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "arson is cool");
	if (!data->window)
		return (1);
	data->game_img.img = NULL;

	data->move.mov_sped = 0.05;
	data->move.rot_sped = 0.05;
	
	direct_player(&data->coords.player);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:09:10 by achbira           #+#    #+#             */
/*   Updated: 2025/03/23 15:44:33 by ychagri          ###   ########.fr       */
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

bool is_border(int x, int y)
{
	return (x <= MAP_X + MAP_BORDER_SIZE || x >= MAP_X + MAP_W - MAP_BORDER_SIZE || y <= MAP_Y + MAP_BORDER_SIZE || y >= MAP_Y + MAP_H - MAP_BORDER_SIZE);
}
 
// bool is_wall(t_data *data, int x, int y)
// {
// 	int player_x; int player_y;

// }

// void draw_minimap(t_data *data)
// {
// 	int x;
// 	int y;

// 	x = MAP_X;
// 	while (x < MAP_X + MAP_W)
// 	{
// 		y = MAP_Y;
// 		while (y < MAP_Y + MAP_H)
// 		{
// 			if (is_border(x, y))
// 				pp(x, y, MAP_BORDER, &data->game_img);
// 			// else if (is_wall(data ,data->coords.player.x,data->coords.player.y, x, y))
// 			// 	pp(x, y, MAP_WALL, &data->game_img);
// 			else
// 				pp(x, y, MAP_COLOR, &data->game_img);
// 			y++;
// 		}
// 		x++;
// 	}
// 	pp(MAP_X + (MAP_W / 2), MAP_Y + (MAP_H / 2), PLAYER_COLOR, &data->game_img);
// }

void	draw_player_on_minimap(t_data *data)
{
	int	x;
	int	y;

	x = MAP_X + (MAP_W * data->coords.player.x / data->coords.width) - (PLAYER_SIZE / 2);
	y = MAP_Y + (MAP_H * data->coords.player.y / data->coords.height) - (PLAYER_SIZE / 2);

	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		for (int j = 0; j < PLAYER_SIZE; j++)
			pp(x + i, y + j, PLAYER_COLOR, &data->game_img);
	}
}


int	is_wall(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	// Convert minimap pixel (x, y) to map grid coordinates
	map_x = (x - MAP_X) * data->coords.width / MAP_W;
	map_y = (y - MAP_Y) * data->coords.height / MAP_H;

	// Prevent out-of-bounds access
	if (map_x < 0 || map_x >= (int)data->coords.width || map_y < 0 || map_y >= (int)data->coords.height)
		return (0); // Treat out-of-bounds as non-wall (safe check)

	// Check if the tile is a wall ('1' = wall)
	if (data->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	color;
	int	map_x;
	int	map_y;

	x = MAP_X;
	while (x < MAP_X + MAP_W)
	{
		y = MAP_Y;
		while (y < MAP_Y + MAP_H)
		{
			map_x = (x - MAP_X) * data->coords.width / MAP_W;
			map_y = (y - MAP_Y) * data->coords.height / MAP_H;
			if (is_wall(data, x, y))
				color = MAP_WALL;  // Wall color 
			else
				color = FLOOR_COLOR;  // Black square
			pp(x, y, color, &data->game_img);
			y++;
		}
		x++;
	}
	draw_player_on_minimap(data);
}




int	game_loop(void *arg)
{
	t_data	*data;

	data = arg;
	clear_canvas(data);
	
	move_player(data);
	
	create_world(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->game_img.img, 0, 0);

	return (0);
}
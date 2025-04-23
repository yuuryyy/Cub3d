/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niminap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:55:50 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/23 17:56:33 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool is_border(int x, int y)
{
	return (x <= MAP_X + MAP_BORDER_SIZE || x >= MAP_X + MAP_W - MAP_BORDER_SIZE
			|| y <= MAP_Y + MAP_BORDER_SIZE || y >= MAP_Y + MAP_H - MAP_BORDER_SIZE);
}
 
void	draw_player_on_minimap(t_data *data)
{
	int	x;
	int	y;
	t_player p;
	p = data->coords.player;
	x = 7 * TILE_WIDTH - (PLAYER_SIZE / 2);
	y = 7 * TILE_WIDTH - (PLAYER_SIZE / 2);
	
	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		for (int j = 0; j < PLAYER_SIZE; j++)
			pp(MAP_X + x + i, MAP_Y + y + j, PLAYER_COLOR, &data->game_img);
	}
}

int	is_wall(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x;
	map_y = y;
	if (map_x < 0 || map_x >= (int)data->coords.width || map_y < 0 || map_y >= (int)data->coords.height)
		return (0x45472F);
	else if (data->map[map_y][map_x] == '1')
		return (MAP_WALL);
	else	
		return (FLOOR_COLOR);
}

float	get_dist(float x, float y,float x1, float y1)
{
	return (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	color;
	t_player p;

	p = data->coords.player;
	p.x -= 7;
	p.y -= 7;
	x = -1;
	while (++x <= 15 * TILE_WIDTH)
	{
		y = -1;
		while (++y <= 15 * TILE_WIDTH)
		{
			float circle;
			circle = get_dist(x, y, 7 * TILE_WIDTH, 7 * TILE_WIDTH);
			if (circle > 7 * TILE_WIDTH && ++y)
				continue;
			else if (circle == 7 * TILE_WIDTH) // map border 
				color = MAP_BORDER;
			else if (!((x + (int)(p.x*TILE_WIDTH))%TILE_WIDTH) || !((y + (int)(p.y*TILE_WIDTH))%TILE_WIDTH)) // tiles' square borders 
				color = MAP_BORDER;
			else
				color = is_wall(data, floor(p.x + (float)x / TILE_WIDTH), floor(p.y + (float)y / TILE_WIDTH));
			pp(MAP_X + x, MAP_Y + y, color, &data->game_img);
		}
	}
	draw_player_on_minimap(data);
}


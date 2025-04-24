/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niminap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:55:50 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/24 15:21:29 by achbira          ###   ########.fr       */
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
	else if (data->map[map_y][map_x] == '2')
		return (0x850020);
	else if (data->map[map_y][map_x] == '3')
		return (0x850020 / 2);
	else
		return (FLOOR_COLOR);
}

float	get_dist(float x, float y,float x1, float y1)
{
	return (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));
}

int	is_on_tile_border(int	x, float px)
{
	return ((x + (int)(px * TILE_WIDTH)) % TILE_WIDTH);
}

int	paint_map(t_data *data, t_player p, int x, int y)
{
	float circle;

	circle = get_dist(x, y, 7 * TILE_WIDTH, 7 * TILE_WIDTH);
	if (circle > 7 * TILE_WIDTH && ++y)
		return (-1);
	else if (circle == 7 * TILE_WIDTH) // map border
		return (MAP_BORDER);
	else if (!is_on_tile_border(x, p.x) || !is_on_tile_border(y, p.y)) // tiles' square borders 
		return (MAP_BORDER);
	else
		return (is_wall(data, p.x + (float)x / TILE_WIDTH, p.y + (float)y / TILE_WIDTH));
}

void	draw_minimap(t_data *data)
{
	int			x;
	int			y;
	int			color;
	t_player	p;

	p = data->coords.player;
	p.x -= 7;
	p.y -= 7;
	x = -1;
	while (++x <= 15 * TILE_WIDTH)
	{
		y = -1;
		while (++y <= 15 * TILE_WIDTH)
		{
			color = paint_map(data, p, x, y);
			if (color == -1)
				continue ;
			pp(MAP_X + x, MAP_Y + y, color, &data->game_img);
		}
	}
	draw_player_on_minimap(data);
}

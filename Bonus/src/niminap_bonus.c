/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niminap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:55:50 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/24 23:13:39 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

float	get_dist(float x, float y, float x1, float y1)
{
	return (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));
}

int	is_on_tile_border(int x, float px)
{
	return ((x + (int)(px * TILE_WIDTH)) % TILE_WIDTH);
}

int	is_wall(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x;
	map_y = y;
	if (map_x < 0 || map_x >= (int)data->coords.width
		|| map_y < 0 || map_y >= (int)data->coords.height)
		return (MAP_WALL);
	else if (data->map[map_y][map_x] == '1')
		return (0x45472F);
	else if (data->map[map_y][map_x] == '2')
		return (0x850020);
	else if (data->map[map_y][map_x] == '3')
		return (0x850020 / 2);
	else
		return (FLOOR_COLOR);
}

int	paint_map(t_data *data, t_player p, int x, int y)
{
	float	circle;

	if (x > 7 * TILE_WIDTH - (PLAYER_SIZE / 2) \
		&& x < 7 * TILE_WIDTH + (PLAYER_SIZE / 2) \
		&& y > 7 * TILE_WIDTH - (PLAYER_SIZE / 2) \
		&& y < 7 * TILE_WIDTH + (PLAYER_SIZE / 2))
		return (PLAYER_COLOR);
	circle = get_dist(x, y, 7 * TILE_WIDTH, 7 * TILE_WIDTH);
	if (circle > 7 * TILE_WIDTH && ++y)
		return (-1);
	else if (circle == 7 * TILE_WIDTH)
		return (MAP_BORDER);
	else if (!((x + (int)(p.x * TILE_WIDTH)) % TILE_WIDTH) \
	|| !((y + (int)(p.y * TILE_WIDTH)) % TILE_WIDTH))
		return (MAP_BORDER);
	else
		return (is_wall(data, p.x + (float)x
				/ TILE_WIDTH, p.y + (float)y / TILE_WIDTH));
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
}

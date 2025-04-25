/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sp_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:30:00 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/25 21:15:01 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	get_coords(t_data *data, int i, int k, char **map)
{
	data->coords.player.pos = player_pos(map[i][k]);
	data->coords.player.x = k;
	data->coords.player.y = i;
	map[i][k] = '0';
	return (true);
}

int	add_sprite(int i, int k, t_data *data)
{
	t_sprite	*sprite;
	t_list		*new;

	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		return (0);
	new = ft_lstnew(sprite);
	if (!new)
		return (free(sprite), 0);
	ft_lstadd_back(&data->sprite, new);
	sprite->x = k + 0.5;
	sprite->y = i + 0.5;
	data->map[i][k] = '0';
	return (1);
}

bool	map_content_check(t_data *data, char **map)
{
	bool	pos;
	int		i;
	int		k;

	pos = false;
	i = -1;
	while (map[++i])
	{
		k = -1;
		while (map[i][++k])
		{
			if (map[i][k] == 'W' || map[i][k] == 'S'
					|| map[i][k] == 'N' || map[i][k] == 'E')
			{
				if (pos)
					return (error(PCONFLCT), free_data(data), false);
				pos = get_coords(data, i, k, map);
			}
			else if (map[i][k] != ' ' && map[i][k] < '0' && map[i][k] > '4')
				return (error(CHARR), free_data(data), false);
			if (map[i][k] == '4')
				add_sprite(i, k, data);
		}
	}
	if (!pos)
		return (error("\tNo player position !!"), free_data(data), false);
	return (true);
}

char	*fill_wall(char *line, int len, t_data *data)
{
	char	*tmp;
	int		i;

	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (free_data(data), error("\tmalloc has failed"), exit(1), NULL);
	i = 0;
	while (line[i])
	{
		tmp[i] = line[i];
		i++;
	}
	free(line);
	while (i < len)
	{
		tmp[i++] = '1';
	}
	tmp[i] = '\0';
	return (tmp);
}

void	rect_map(char **map, t_data *data)
{
	int		i;
	int		k;

	i = -1;
	while (map[++i])
	{
		k = -1;
		while (map[i][++k])
		{
			if (map[i][k] == ' ')
				map[i][k] = '1';
		}
	}
	i = -1;
	while (map[++i])
	{
		if (ft_strlen(map[i]) < data->coords.width)
			map[i] = fill_wall(map[i], data->coords.width, data);
	}
}

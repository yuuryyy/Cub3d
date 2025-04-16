/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sp_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:30:00 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/16 10:04:34 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	map_content_check(t_data *data, char **map)
{
	bool	pos;
	int		i;
	int		k;

	pos = false;
	i = -1;
	while(map[++i])
	{
		k = -1;
		while (map[i][++k])
		{
			if (map[i][k] == 'W' || map[i][k] == 'S' || map[i][k] == 'N' || map[i][k] == 'E')
			{
				if (pos)
					return (error(PCONFLCT), free_data(data), false);
				pos = true;
				data->coords.player.pos = player_pos(map[i][k]);
				data->coords.player.x = k;
				data->coords.player.y = i;
				map[i][k] = '0';
			}
			else if (map[i][k] != ' ' && map[i][k] != '1' && map[i][k] != '0' && map[i][k] != '2')
				return (error("\tInvalid characters !!"), free_data(data), false);
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

// void	path(char **map, t_map size, size_t x, size_t y)
// {
// 	if (x < 0 || x >= size.width || y < 0 || y >= size.height
// 		|| map[y][x] == '1' || map[y][x] == 'x')
// 		return ;
// 	map[y][x] = 'x';
// 	path(map, size, x - 1, y);
// 	path(map, size, x + 1, y);
// 	path(map, size, x, y - 1);
// 	path(map, size, x, y + 1);
// }

// char	**expand_inpath(t_data *data)
// {
// 	char	**tmp;
// 	int		i;
// 	int		k;

// 	tmp = ft_calloc((data->coords.height + 1) , sizeof(char *));
// 	if (!tmp)
// 		return (free_data(data), error("\tmalloc failed."), NULL);
// 	i = -1;
// 	while (data->map[++i])
// 	{
// 		k = -1;
// 		tmp[i] = ft_calloc(ft_strlen(data->map[i]) + 1, sizeof(char));
// 		if (!tmp[i])
// 			return (free_array(tmp),free_data(data), error("\tmalloc failed."), NULL);
// 		while (data->map[i][++k])
// 			tmp[i][k] = data->map[i][k];
// 		tmp[i][k] = 0;
// 	}
// 	path(tmp, data->coords, data->coords.player.x, data->coords.player.y);
// 	return (tmp);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:06:26 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/15 18:15:38 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	emptyln_check(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (map[i] && !is_empty(map[i]))
		i++;
	while (map[i] && is_empty(map[i]))
		i++;
	if (map[i] && !is_empty(map[i]))
		return (free_data(data), error(EMPTYLN), 1);
	return (0);
}

int	trim_map(t_data *data, char **map)
{
	int		max;
	int		len;
	int		i;

	i = array_len(map) - 1;
	while (map[i] && is_empty(map[i]))
	{
		free(map[i]);
		map[i] = NULL;
		i--;
	}
	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]) - 1;
		if (map[i][len] == '\n')
			map[i][len] = '\0';
		if (max < len)
			max = len;
		i++;
	}
	data->coords.height = i;
	data->coords.width = max;
	return (0);
}


bool	space_check(char *line1, char *line2)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line1[i] && line2 && line2[i])
	{
		if ((line1[i] == ' ' && line2[i] != ' ' && line2[i] != '1')
			|| (line2[i] == ' ' && line1[i] != ' ' && line1[i] != '1'))
			return (false);
		i++;
	}
	// printf("%s\n", line2);
	if (!line1[i] && !line2[i])
		return (true);
	else if (!line1[i])
		tmp = line2;
	else
		tmp = line1;
	while (tmp[i])
	{
		if (tmp[i] != '1' && tmp[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	check_walls(t_data *data, char **map)
{
	size_t		i;
	int			k;
	char	*tmp;

	i = -1;
	while (map[++i])
	{
		// printf("%s\n", map[i]);
		if (space_check(map[i], map[i + 1]) == false)
			return (free_data(data), error("\tWhite space unclosed!!"), false);
		tmp = ft_strtrim(map[i], " ");
		k = 0;
		if (i == 0 || i == data->coords.height - 1)
		{
			while (tmp[k])
			{
				if (tmp[k] != '1' && tmp[k] != ' ')
					return (free(tmp), free_data(data),error("\tUnclosed map!"),false);
				k++;
			}
		}
		else if (tmp[0] != '1' || tmp[ft_strlen(tmp) - 1] != '1')
			return (free(tmp), free_data(data),error("\tUnclosed map"),false);
		free(tmp);
	}
	return (true);
}

int	check_data(t_data *data, char **av)
{
	if (get_data(data, av) || emptyln_check(data->map, data))
		return (1);
	if (!data->map || !*data->map)
		return (free_data(data), error("\tNo map No mad."), 1);
	trim_map(data, data->map);
	if (!check_walls(data, data->map) || !map_content_check(data, data->map))
		return (1);
	rect_map(data->map, data);
	// tmp = expand_inpath(data);
	// if (!tmp)
	// 	return (1);
	// i = -1;
	// while (tmp[++i])
	// {
	// 	printf("%s\n", tmp[i]);
	// 	k = -1;
	// 	while (tmp[i][++k])
	// 		if (tmp[i][k] != '1' && tmp[i][k] != 'x')
	// 			return (free_array(tmp),free_data(data), error("\tInvalid path."), 1);
	// }
	return (0);
}

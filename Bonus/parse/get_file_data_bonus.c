/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:30:34 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/24 18:16:27 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


char	*valid_txtr(char *texture)
{
	char	*str;
	char	*tmp;

	str = ft_strchr(texture, ' ', '\t');
	if (!str || is_empty(str))
		return (error(CE), NULL);
	tmp = ft_strtrim(str, " \t\n");
	free(texture);
	return (tmp);
}

char	*valid_color(char *color)
{
	char	**split;
	char	*textr;
	int		k;
	int		i;

	textr = valid_txtr(color);
	split = ft_split(textr, ',');
	if (!split)
		return (error("\tmalloc failed"), NULL);
	if (array_len(split) != 3)
		return (error(CE), free_array(split), NULL);
	i = -1;
	while (split[++i])
	{
		k = -1;
		while (split[i][++k])
		{
			if (split[i][k] > '9' || split[i][k] < '0')
				return (error(CE), free_array(split), NULL);
		}
		if (k > 3 || k < 1 || ft_atoi(split[i]) > 255 || ft_atoi(split[i]) < 0)
			return (error(CE), free_array(split), NULL);
	}
	free_array(split);
	return (textr);
}

int	check_textures(t_data *data, t_list *content)
{
	data->textures->c_color = valid_color(data->textures->c_color);
	if (!data->textures->c_color)
		return (ft_lstclear(&content, free_del), 1);
	data->textures->f_color = valid_color(data->textures->f_color);
	if (!data->textures->f_color)
		return (ft_lstclear(&content, free_del), 1);
	data->textures->no_txtr = valid_txtr(data->textures->no_txtr);
	if (!data->textures->no_txtr)
		return (ft_lstclear(&content, free_del), 1);
	data->textures->we_txtr = valid_txtr(data->textures->we_txtr);
	if (!data->textures->we_txtr)
		return (ft_lstclear(&content, free_del), 1);
	data->textures->so_txtr = valid_txtr(data->textures->so_txtr);
	if (!data->textures->so_txtr)
		return (ft_lstclear(&content, free_del), 1);
	data->textures->ea_txtr = valid_txtr(data->textures->ea_txtr);
	if (!data->textures->ea_txtr)
		return (ft_lstclear(&content, free_del), 1);
	return (0);
}

int	get_color(char *color)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(color, ',');
	if (!split)
		return (error("\tmalloc failed"), -1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_array(split);
	return (r << 16 | g << 8 | b);
}

int	get_data(t_data *data, char **av)
{
	t_list		*content;

	content = get_file_content(av[1]);
	data->textures = ft_calloc(1, sizeof(t_textures));
	if (!data->textures)
		return (ft_lstclear(&content, free_del), 1);
	if (!content || get_textures(content, data))
		return (free_data(data), 1);
	if (check_textures(data, content))
		return (free_data(data), 1);
	data->map = get_map(content);
	ft_lstclear(&content, free_del);
	if (!data->map)
		return (free_data(data), error("Failed to get the map"), 1);
	data->colors.c_color = get_color(data->textures->c_color);
	data->colors.f_color = get_color(data->textures->f_color);
	return (0);
}

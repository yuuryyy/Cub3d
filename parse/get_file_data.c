/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:30:34 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/15 22:56:54 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"


char	*valid_txtr(char *texture)
{
	char	*str;
	char	*tmp;

	str = ft_strchr(texture, ' ', '\t');
	if (!str || is_empty(str))
		return (error(CONFERR), NULL);
	tmp = ft_strtrim(str, " \t");
	free(texture);
	return (tmp);
}

int	check_textures(t_data *data, t_list *content)
{
	data->textures->c_color = valid_txtr(data->textures->c_color);
	if (!data->textures->c_color)
		return (ft_lstclear(&content, free_del), 1);//free textures
	data->textures->f_color = valid_txtr(data->textures->f_color);
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
		return (1);
		// while (1)
	// {
	// 	;
	// }
	data->map = get_map(content);
	ft_lstclear(&content, free_del);
	if (!data->map)
		return (free_data(data), error("Failed to get the map"), 1); //free data struct
	return (0);
}

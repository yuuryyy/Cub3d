/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:57:26 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/15 23:08:02 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	free_array(char	**str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	array_len(char **str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_del(void *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->textures)
	{
		printf("in\n");
		if(data->textures->no_txtr)
			free_del(data->textures->no_txtr);
		if(data->textures->so_txtr)
			free_del(data->textures->so_txtr);
		if(data->textures->we_txtr)
			free_del(data->textures->we_txtr);
		if(data->textures->ea_txtr)
			free_del(data->textures->ea_txtr);
		if(data->textures->f_color)
		{
			free_del(data->textures->f_color);
		}
		if(data->textures->c_color)
			free_del(data->textures->c_color);
		free_del(data->textures);
	}
	if (data->map)
		free_array(data->map);
	ft_bzero(data, sizeof(t_data));
	data = NULL;
}

t_position	player_pos(char c)
{
	if (c == 'W')
		return (west);
	else if (c == 'S')
		return (south);
	else if (c == 'N')
		return (north);
	else if (c == 'E')
		return (east);
	return(0);
}
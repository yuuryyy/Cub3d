/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:57:26 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/15 18:15:38 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
		if(data->ready_tex.no_txtr.img.img)
			mlx_destroy_image(data->mlx, data->ready_tex.no_txtr.img.img);
		if(data->ready_tex.so_txtr.img.img)
			mlx_destroy_image(data->mlx, data->ready_tex.so_txtr.img.img);
		if(data->ready_tex.we_txtr.img.img)
			mlx_destroy_image(data->mlx, data->ready_tex.we_txtr.img.img);
		if(data->ready_tex.ea_txtr.img.img)
			mlx_destroy_image(data->mlx, data->ready_tex.ea_txtr.img.img);

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
	if (data->game_img.img)
		mlx_destroy_image(data->mlx, data->game_img.img);
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
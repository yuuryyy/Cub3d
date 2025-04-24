/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:03:27 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/24 18:36:34 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	error(char *err)
{
	ft_putstr_fd(RED"ERROR :\n"BLUE, 2);
	ft_putendl_fd(err, 2);
	ft_putstr_fd(RESET, 2);
}

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	if (!line || !*line || *line == '\n')
		return (true);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] && line[i] != '\n')
		return (false);
	return (true);
}

void	destroy_textures(t_data *data)
{
	int i;

	i = -1;
	if (data->ready_tex.no_txtr.img.img)
		mlx_destroy_image(data->mlx, data->ready_tex.no_txtr.img.img);
	if (data->ready_tex.so_txtr.img.img)
		mlx_destroy_image(data->mlx, data->ready_tex.so_txtr.img.img);
	if (data->ready_tex.we_txtr.img.img)
		mlx_destroy_image(data->mlx, data->ready_tex.we_txtr.img.img);
	if (data->ready_tex.ea_txtr.img.img)
		mlx_destroy_image(data->mlx, data->ready_tex.ea_txtr.img.img);
	while (++i < 19)
		if (data->sprites.texpm[i].img.img)
			mlx_destroy_image(data->mlx, data->sprites.texpm[i].img.img);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->textures)
	{
		destroy_textures(data);
		if (data->textures->no_txtr)
			free_del(data->textures->no_txtr);
		if (data->textures->so_txtr)
			free_del(data->textures->so_txtr);
		if (data->textures->we_txtr)
			free_del(data->textures->we_txtr);
		if (data->textures->ea_txtr)
			free_del(data->textures->ea_txtr);
		if (data->textures->f_color)
			free_del(data->textures->f_color);
		if (data->textures->c_color)
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

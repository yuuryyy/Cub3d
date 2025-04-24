/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_loading_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:55:30 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/24 15:10:02 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	destroy_texture(t_loaded_tex *tex, void *mlx)
{
	if (tex->img.img)
	{
		mlx_destroy_image(mlx, tex->img.img);
		tex->img.img = NULL;
	}
}

void	destroy_all_textures(t_ready_tex *textures, void *mlx)
{
	destroy_texture(&textures->no_txtr, mlx);
	destroy_texture(&textures->so_txtr, mlx);
	destroy_texture(&textures->ea_txtr, mlx);
	destroy_texture(&textures->we_txtr, mlx);
}

void	load_texture(t_data *data, t_loaded_tex *tex, void *mlx, char *file)
{
	tex->img.img = mlx_xpm_file_to_image(mlx, file, &tex->width, &tex->height);
	if (!tex->img.img) // destroy raycasting data TODO:
	{
		free_data(data);
		destroy_all_textures(&data->ready_tex, data->mlx);
		error("Texture loading failed");
		exit(1);
	}
	tex->img.addr = mlx_get_data_addr(tex->img.img, \
		&tex->img.bits_per_pixel, \
		&tex->img.line_length, \
		&tex->img.endian);
	if (!tex->img.addr)
	{
		destroy_texture(tex, mlx);
		free_data(data);
		destroy_all_textures(&data->ready_tex, data->mlx);
		error("image addressing failed");
		exit(1);
	}
}

void	load_all_textures(t_ready_tex *textures, void *mlx, t_data *data)
{
	// printf("Loading textures\n");
	load_texture(data, &textures->no_txtr, mlx, data->textures->no_txtr);
	load_texture(data, &textures->so_txtr, mlx, data->textures->so_txtr);
	load_texture(data, &textures->ea_txtr, mlx, data->textures->ea_txtr);
	load_texture(data, &textures->we_txtr, mlx, data->textures->we_txtr);
    load_texture(data, &data->sprites.texpm[0], mlx, "textures/fire/fire00.xpm");
    load_texture(data, &data->sprites.texpm[1], mlx, "textures/fire/fire01.xpm");
    load_texture(data, &data->sprites.texpm[2], mlx, "textures/fire/fire02.xpm");
    load_texture(data, &data->sprites.texpm[3], mlx, "textures/fire/fire03.xpm");
    load_texture(data, &data->sprites.texpm[4], mlx, "textures/fire/fire04.xpm");
    load_texture(data, &data->sprites.texpm[5], mlx, "textures/fire/fire05.xpm");
    load_texture(data, &data->sprites.texpm[6], mlx, "textures/fire/fire06.xpm");
    load_texture(data, &data->sprites.texpm[7], mlx, "textures/fire/fire07.xpm");
    load_texture(data, &data->sprites.texpm[8], mlx, "textures/fire/fire08.xpm");
    load_texture(data, &data->sprites.texpm[9], mlx, "textures/fire/fire09.xpm");
    load_texture(data, &data->sprites.texpm[10], mlx, "textures/fire/fire10.xpm");
    load_texture(data, &data->sprites.texpm[11], mlx, "textures/fire/fire11.xpm");
    load_texture(data, &data->sprites.texpm[12], mlx, "textures/fire/fire12.xpm");
    load_texture(data, &data->sprites.texpm[13], mlx, "textures/fire/fire13.xpm");
    load_texture(data, &data->sprites.texpm[14], mlx, "textures/fire/fire14.xpm");
    load_texture(data, &data->sprites.texpm[15], mlx, "textures/fire/fire15.xpm");
    load_texture(data, &data->sprites.texpm[16], mlx, "textures/fire/fire16.xpm");
    load_texture(data, &data->sprites.texpm[17], mlx, "textures/fire/fire17.xpm");
    load_texture(data, &data->sprites.texpm[18], mlx, "textures/fire/fire18.xpm");
}

t_loaded_tex	*get_texture(t_data *data, t_ray *ray)
{
	if (ray->v_h)
	{
		if (ray->dir.y < 0)
			return (&data->ready_tex.no_txtr);
		return (&data->ready_tex.so_txtr);
	}
	else
	{
		if (ray->dir.x < 0)
			return (&data->ready_tex.ea_txtr);
		return (&data->ready_tex.we_txtr);
	}
	return (NULL);
}

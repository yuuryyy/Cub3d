/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_loading_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:55:30 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/25 10:09:28 by achbira          ###   ########.fr       */
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
	if (!tex->img.img)
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
	load_texture(data, &textures->no_txtr, mlx, data->textures->no_txtr);
	load_texture(data, &textures->so_txtr, mlx, data->textures->so_txtr);
	load_texture(data, &textures->ea_txtr, mlx, data->textures->ea_txtr);
	load_texture(data, &textures->we_txtr, mlx, data->textures->we_txtr);
	load_texture(data, &data->s_tex[0], mlx, FIRE00);
	load_texture(data, &data->s_tex[1], mlx, FIRE01);
	load_texture(data, &data->s_tex[2], mlx, FIRE02);
	load_texture(data, &data->s_tex[3], mlx, FIRE03);
	load_texture(data, &data->s_tex[4], mlx, FIRE04);
	load_texture(data, &data->s_tex[5], mlx, FIRE05);
	load_texture(data, &data->s_tex[6], mlx, FIRE06);
	load_texture(data, &data->s_tex[7], mlx, FIRE07);
	load_texture(data, &data->s_tex[8], mlx, FIRE08);
	load_texture(data, &data->s_tex[9], mlx, FIRE09);
	load_texture(data, &data->s_tex[10], mlx, FIRE10);
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

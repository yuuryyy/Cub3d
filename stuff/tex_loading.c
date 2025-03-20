/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:55:30 by ychagri           #+#    #+#             */
/*   Updated: 2025/03/20 03:31:25 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void destroy_texture(t_loaded_tex *tex, void *mlx)
{
    if (tex->img.img)
    {
        mlx_destroy_image(mlx, tex->img.img);
        tex->img.img = NULL;
    }
}

void destroy_all_textures(t_ready_tex *textures, void *mlx)
{
    destroy_texture(&textures->no_txtr, mlx);
    destroy_texture(&textures->so_txtr, mlx);
    destroy_texture(&textures->ea_txtr, mlx);
    destroy_texture(&textures->we_txtr, mlx);
}

void load_texture(t_data *data, t_loaded_tex *tex, void *mlx, char *file)
{
	
	tex->img.img = mlx_xpm_file_to_image(mlx, file, &tex->width, &tex->height);
    if (!tex->img.img)
    {//destroy raycasting data TODO:
        free_data(data);
        destroy_all_textures(&data->ready_tex, data->mlx);
        error("Texture loading failed");
        exit(1);
    }
    tex->img.addr = mlx_get_data_addr(tex->img.img, 
                                      &tex->img.bits_per_pixel, 
                                      &tex->img.line_length, 
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


void load_all_textures(t_ready_tex *textures, void *mlx, t_data *data)
{
    // printf("Loading textures\n");
    load_texture(data, &textures->no_txtr, mlx, data->textures->no_txtr);
	load_texture(data, &textures->so_txtr, mlx, data->textures->so_txtr);
    load_texture(data, &textures->ea_txtr, mlx, data->textures->ea_txtr);
    load_texture(data, &textures->we_txtr, mlx, data->textures->we_txtr);
}

t_loaded_tex *get_texture(t_data *data, t_ray *ray)
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


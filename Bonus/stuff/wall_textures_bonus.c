/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:48:48 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/16 10:19:49 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d_bonus.h"

int	get_tex_x(t_ray *r, t_loaded_tex *tex, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (float)tex->width);
	if ((r->v_h && r->dir.y > 0) || (!r->v_h && r->dir.x < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

int	max(int a, int b)
{
	return (a * (a > b) + b * (b >= a));
}

int	more_color(int color)
{
	int r;
	int g;
	int b;

	r = max(((color >> 16) & 0xFF) * 4, 255);
	g = max(((color >> 8) & 0xFF) * 4, 255);
	b = max((color & 0xFF) * 4, 255);
	
	return ((r << 16) + (g << 8) + b);
}

int	draw_wall_stripe(t_ray *r, t_data *all, int x, t_loaded_tex *tex)
{
	int		y;
	int		tex_x;
	int		tex_y;
	float	step;
	float	tex_pos;

	tex_x = get_tex_x(r, tex, r->wall_x);
	step = 1.0 * tex->height / r->line_h;
	tex_pos = (r->start - HEIGHT / 2 + r->line_h / 2) * step;
	y = r->start - 1;
	while (++y < r->end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		r->color = *(unsigned int *)(tex->img.addr +
				(tex_y * tex->img.line_length +
					tex_x * (tex->img.bits_per_pixel / 8)));
		if (r->hit_wall == '2')
			r->color = more_color(r->color);
		pp(x, y, r->color, &all->game_img);
	}
	return (y);
}

int	build_wall_stripe(t_ray *r, t_data *all, int x)
{
	t_loaded_tex	*tex;

	r->wall_dist = r->side.x - r->delta.x;
	if (r->v_h)
		r->wall_dist = r->side.y - r->delta.y;
	r->line_h = (int)(HEIGHT / r->wall_dist);
	r->start = fmax(HEIGHT / 2 - r->line_h / 2, 0);
	r->end = fmin(HEIGHT / 2 + r->line_h / 2, HEIGHT - 1);
	tex = get_texture(all, r);
	if (r->v_h)
		r->wall_x = all->coords.player.x + r->wall_dist * r->dir.x;
	else
		r->wall_x = all->coords.player.y + r->wall_dist * r->dir.y;
	r->wall_x -= floor(r->wall_x);
	return (draw_wall_stripe(r, all, x, tex));
}


// int	build_wall_stripe(t_ray *r, t_data *all, int x)
// {
// 	int		y;
// 	float	wall_x;
// 	int		tex_x;
// 	int		tex_y;
// 	t_loaded_tex	*tex;
// 	float step;
// 	float tex_pos;

// 	r->wall_dist = r->side.x - r->delta.x;
// 	if (r->v_h)
// 		r->wall_dist = r->side.y - r->delta.y;
// 	r->line_h = (int)(HEIGHT / r->wall_dist);
// 	r->start = fmax(HEIGHT / 2 - r->line_h / 2, 0);
// 	r->end = fmin(HEIGHT / 2 + r->line_h / 2, HEIGHT - 1);
	
// 	tex = get_texture(all, r);
// 	if (r->v_h)
// 		wall_x = all->coords.player.x + r->wall_dist * r->dir.x;
// 	else
// 		wall_x = all->coords.player.y + r->wall_dist * r->dir.y;
		
// 	//to here
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * (float)tex->width);
// 	if ((r->v_h && r->dir.y > 0) || (!r->v_h && r->dir.x < 0))
// 		tex_x = tex->width - tex_x - 1;

// 	step = 1.0 * tex->height / r->line_h;
// 	tex_pos = (r->start - HEIGHT / 2 + r->line_h / 2) * step;
	
// 	y = r->start - 1;
// 	while (++y < r->end)
// 	{
// 		tex_y = (int)tex_pos;
// 		if (tex_y >= tex->height)
// 			tex_y = tex->height - 1;
// 		tex_pos += step;

// 		r->color = *(unsigned int *)(tex->img.addr +
// 						(tex_y * tex->img.line_length +
// 							 tex_x * (tex->img.bits_per_pixel / 8)));
// 		pp(x, y, r->color, &all->game_img);
// 	}
// 	return (y); 
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:33 by achbira           #+#    #+#             */
/*   Updated: 2025/03/13 20:49:55 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	pp(int x, int y, int color, t_img *data)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = (data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

void	what_is_ray(t_player p, t_ray *ray, int x)
{
	float	camera_x;

	ray->map_x = floor(p.x);
	ray->map_y = floor(p.y);
	camera_x = 2 * x / (float)WIDTH - 1;
	ray->dir.x = p.dir.x + p.plane.x * camera_x + 0.00001;
	ray->dir.y = p.dir.y + p.plane.y * camera_x + 0.00001;
	ray->delta.x = fabs(1 / ray->dir.x);
	ray->delta.y = fabs(1 / ray->dir.y);
	ray->side.x = (float)(ray->map_x + 1 - p.x) * ray->delta.x;
	if (ray->dir.x < 0)
		ray->side.x = (float)(p.x - ray->map_x) * ray->delta.x;
	ray->side.y = (float)(ray->map_y + 1 - p.y) * ray->delta.y;
	if (ray->dir.y < 0)
		ray->side.y = (float)(p.y - ray->map_y) * ray->delta.y;
	ray->step.x = 1 - 2 * (ray->dir.x < 0);
	ray->step.y = 1 - 2 * (ray->dir.y < 0);
	ray->v_h = 0;
	ray->hit_wall = 0;
}

void	send_rays(t_ray *r, t_player *p, t_data *all, int x)
{
	int		depth;
	
	depth = 100;
	what_is_ray(*p, r, x);
	while (!r->hit_wall && depth--)
	{
		if (r->side.x < r->side.y)
		{
			r->side.x += r->delta.x;
			r->map_x += r->step.x;
			r->v_h = 0;
		}
		else
		{
			r->side.y += r->delta.y;
			r->map_y += r->step.y;
			r->v_h = 1;
		}
		if (!(r->map_y >= 0 && r->map_y < (int)all->coords.height \
			&& r->map_x >= 0 && r->map_x < (int)all->coords.width))
			continue;
		else if (all->map[r->map_y][r->map_x] != '0')
			r->hit_wall = all->map[r->map_y][r->map_x];
	}
}

int	build_wall_stripe(t_ray *r, t_data *all, int x)
{
	int		y;

	r->wall_dist = r->side.x - r->delta.x;
	if (r->v_h)
		r->wall_dist = r->side.y - r->delta.y;
	r->line_h = (int)(HEIGHT / r->wall_dist);
	r->start = fmax(HEIGHT / 2 - r->line_h / 2, 0);
	r->end = fmin(HEIGHT / 2 + r->line_h / 2, HEIGHT - 1);
	r->color = 0x37ff7f50;
	y = r->start - 1;
	while (++y < r->end)
		pp(x, y, r->color, &all->game_img);
	return (y);
}

void	create_world(t_data *all)
{
	t_player	*p;
	t_ray		r;
	int			x;
	int			y;

	p = &all->coords.player;
	x = -1;
	while (++x < WIDTH)
	{
		send_rays(&r, p, all, x);
		y = HEIGHT / 2;
		if (r.hit_wall)
			y = build_wall_stripe(&r, all, x);
		while (++y < HEIGHT)
		{
			pp(x, y, all->colors.f_color ,&all->game_img);
			int y2 = (float)HEIGHT - y;
			pp(x, y2, all->colors.c_color ,&all->game_img);
		}
	}
	pp(WIDTH / 2, HEIGHT / 2, 0xFFFFFF, &all->game_img);
}

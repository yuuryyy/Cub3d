/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_go_brrr_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:33 by achbira           #+#    #+#             */
/*   Updated: 2025/04/24 15:13:10 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	pp(int x, int y, int color, t_img *data)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = (data->addr + (y * data->line_length + x * \
	(data->bits_per_pixel / 8)));
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
			continue ;
		else if (all->map[r->map_y][r->map_x] != '0' && all->map[r->map_y][r->map_x] != '3')
			r->hit_wall = all->map[r->map_y][r->map_x];
		if (x == WIDTH / 2 && (all->map[r->map_y][r->map_x] == '2' || all->map[r->map_y][r->map_x] == '3'))
		{
			p->target_door.x = r->map_x;
			p->target_door.y = r->map_y;
		}
	}
}


void	i_see_ded_ppl(t_data *data, float *dists, t_sprite s)
{
	int	color;
	int	d;
	int	x;
	int	y;
	
	x = s.start_x - 1;
	printf("%f\n", data->sprite_idx);
	while (++x < s.end_x)
	{
		s.tx = ((x - (s.screenx - s.w / 2)) * s.texpm[(int)data->sprite_idx].width / s.w);
		if (s.yproj < 0 || (int)s.yproj > (int)dists[x])
			continue ;
		y = s.start_y - 1;
		while (++y < s.end_y)
		{
			d = y - s.start_y;
			s.ty = (d * s.texpm[(int)data->sprite_idx].height) / s.h;
			if (!(s.tx < 0 || s.tx > 64 ||s.ty < 0 || s.ty > 64))
				color = ((int *)s.texpm[(int)data->sprite_idx].img.addr)[s.ty * s.texpm[(int)data->sprite_idx].width + s.tx];
			else 
				color = 0;
			if((color & 0x00ffff) != 0)
				pp(x, y, color, &data->game_img);
		}
	}
}

void	sprites(t_data *data, float *dists, t_player p)
{
	t_sprite	s;
	float		inverse;

	s = data->sprites;
	s.x -= p.x;
	s.y -= p.y;

	inverse = (float)1 / (p.plane.x * p.dir.y - p.dir.x * p.plane.y);
	
	s.xproj = inverse * (s.x * p.dir.y - s.y * p.dir.x);
	s.yproj = inverse * (s.y * p.plane.x - s.x * p.plane.y);
	
	s.screenx = (WIDTH / 2) * (1 + s.xproj / s.yproj);

	s.h = fabs(HEIGHT / s.yproj);
	s.start_y = fmax(0, HEIGHT / 2 - s.h / 2);
	s.end_y = fmin(HEIGHT - 1, HEIGHT / 2 + s.h / 2);
	s.w = fabs(WIDTH / s.yproj);
	s.start_x = fmax(0, s.screenx - s.w / 2);
	s.end_x = fmin(WIDTH - 1, s.screenx + s.w / 2); 
	
	i_see_ded_ppl(data, dists, s);
}


void	create_world(t_data *all)
{
	t_player	*p;
	t_ray		r;
	int			x;
	int			y;
	float		wall_dists[WIDTH + 1];

	p = &all->coords.player;
	p->target_door.x = -1;
	x = -1;
	while (++x < WIDTH)
	{
		wall_dists[x] = -1;
		send_rays(&r, p, all, x);
		y = HEIGHT / 2;
		if (r.hit_wall)
		{
			y = build_wall_stripe(&r, all, x);
			wall_dists[x] = r.wall_dist;		
		}
		while (++y < HEIGHT)
		{
			pp(x, y, all->colors.f_color, &all->game_img);
			pp(x, HEIGHT - y, all->colors.c_color, &all->game_img);
		}
	}

	all->sprites.x = 26.5;
	all->sprites.y = 1.3;
	if ((int)p->x == (int)all->sprites.x && (int)p->y == (int)all->sprites.y)
		x_exit(all);
	sprites(all, wall_dists, *p);
	pp(WIDTH / 2, HEIGHT / 2, 0xFFFFFF, &all->game_img);
}

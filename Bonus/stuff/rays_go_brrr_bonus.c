/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_go_brrr_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:33 by achbira           #+#    #+#             */
/*   Updated: 2025/04/25 00:36:59 by achbira          ###   ########.fr       */
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

void	heaven_and_earth(t_data *data, t_ray *r, int x)
{
	int	y;

	y = HEIGHT / 2;
	if (r->hit_wall)
	{
		y = build_wall_stripe(r, data, x);
		data->wall_dists[x] = r->wall_dist;
	}
	while (++y < HEIGHT)
	{
		pp(x, y, data->colors.f_color, &data->game_img);
		pp(x, HEIGHT - y, data->colors.c_color, &data->game_img);
	}	
}

void	sort_arr(t_data *data)
{
	int			i;
	int			j;
	t_sprite	*s;
	t_sprite	tmp;

	s = data->sprites;
	i = -1;
	while (++i < 2)
	{
		j = i;
		while (++j < 2)
		{
			if (s[i].player_dist < s[j].player_dist)
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
		}
	}
}

void	sprites_distances(t_data *data, t_player p)
{
	t_sprite	*s;
	int			i;

	s = data->sprites;
	i = -1;
	while (++i < 2)
	{
		s[i].player_dist = get_dist(s[i].x, s[i].y, p.x, p.y);
	}
	sort_arr(data);
}

void	create_world(t_data *data)
{
	t_player	*p;
	t_ray		r;
	int			x;

	p = &data->coords.player;
	p->target_door.x = -1;
	x = -1;
	while (++x < WIDTH)
	{
		data->wall_dists[x] = -1;
		send_rays(&r, p, data, x);
		heaven_and_earth(data, &r, x);
	}
	data->sprites[1] = data->sprites[0];
	data->sprites[0].x = 26.5;
	data->sprites[0].y = 1.3;
	data->sprites[1].x = 30.5;
	data->sprites[1].y = 2.3;
	sprites_distances(data, *p);
	sprites(data, data->wall_dists, *p, data->sprites[0]);
}

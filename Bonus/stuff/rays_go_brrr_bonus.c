/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_go_brrr_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:33 by achbira           #+#    #+#             */
/*   Updated: 2025/04/25 11:06:04 by achbira          ###   ########.fr       */
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
	void	*tmp;
	t_list	*lst;
	t_list	*lst2;

	lst = data->sprite;
	while (lst)
	{
		lst2 = lst->next;
		while (lst2)
		{
			if (((t_sprite *)lst->content)->player_dist \
				< ((t_sprite *)lst2->content)->player_dist)
			{
				tmp = lst->content;
				lst->content = lst2->content;
				lst2->content = tmp;
			}
			lst2 = lst2->next;
		}
		lst = lst->next;
	}
}

void	sprites_distances(t_data *data, t_player p, t_list	**list)
{
	t_sprite	*s;
	t_list		*lst;

	lst = *list;
	while (lst)
	{
		s = lst->content;
		s->player_dist = get_dist(s->x, s->y, p.x, p.y);
		lst = lst->next;
	}
	sort_arr(data);
	lst = *list;
	while (lst)
	{
		sprites(data, data->wall_dists, p, *(t_sprite *)lst->content);
		lst = lst->next;
	}
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
	sprites_distances(data, *p, &data->sprite);
}

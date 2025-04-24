/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_rays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:41:19 by achbira           #+#    #+#             */
/*   Updated: 2025/04/24 21:41:25 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	wall_or_no_wall(t_ray *r, t_data *data, t_player *p, int x)
{
	if (!(r->map_y >= 0 && r->map_y < (int)data->coords.height \
		&& r->map_x >= 0 && r->map_x < (int)data->coords.width))
		return ;
	else if (data->map[r->map_y][r->map_x] != '0' \
		&& data->map[r->map_y][r->map_x] != '3')
		r->hit_wall = data->map[r->map_y][r->map_x];
	if (x == WIDTH / 2 \
		&& (data->map[r->map_y][r->map_x] == '2' \
		|| data->map[r->map_y][r->map_x] == '3'))
	{
		p->target_door.x = r->map_x;
		p->target_door.y = r->map_y;
	}
}

void	send_rays(t_ray *r, t_player *p, t_data *data, int x)
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
		wall_or_no_wall(r, data, p, x);
	}
}

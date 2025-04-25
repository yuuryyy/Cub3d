/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:34:47 by achbira           #+#    #+#             */
/*   Updated: 2025/04/24 19:12:20 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	use_legs(t_vect vec, int neo, t_player *p, t_data *all)
{
	float	x;
	float	y;
	float	border;

	border = (float)1 / 16;
	x = p->x + neo * vec.x * (all->move.mov_sped + border);
	y = p->y + neo * vec.y * (all->move.mov_sped + border);
	if (y > 0 && y < all->coords.height
		&& (all->map[(int)y][(int)p->x] != '1'
		&& all->map[(int)y][(int)p->x] != '2'))
		p->y = p->y + neo * vec.y * all->move.mov_sped;
	if (x > 0 && x < all->coords.width
		&& (all->map[(int)p->y][(int)x] != '1'
		&& all->map[(int)p->y][(int)x] != '2'))
		p->x = p->x + neo * vec.x * all->move.mov_sped;
}

void	use_hips(float angle, t_player *p)
{
	float	oldx;

	oldx = p->dir.x;
	p->dir.x = p->dir.x * cos(angle) - p->dir.y * sin(angle);
	p->dir.y = oldx * sin(angle) + p->dir.y * cos(angle);
	oldx = p->plane.x;
	p->plane.x = p->plane.x * cos(angle) - p->plane.y * sin(angle);
	p->plane.y = oldx * sin(angle) + p->plane.y * cos(angle);
}

void	move_player(t_data *all)
{
	t_player	*p;

	p = &all->coords.player;
	if (all->move.w)
		use_legs(p->dir, 1, p, all);
	if (all->move.s)
		use_legs(p->dir, -1, p, all);
	if (all->move.a)
		use_legs(p->plane, -1, p, all);
	if (all->move.d)
		use_legs(p->plane, 1, p, all);
	if (all->move.rl)
		use_hips(-all->move.rot_sped, p);
	if (all->move.rr)
		use_hips(all->move.rot_sped, p);
}

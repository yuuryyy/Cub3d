#include "cub3d_parse.h"

void	use_more_legs(float x, float y, t_player *p, t_data *all)
{
	if ((y + p->y) >= 0 && (int)(y + p->y) < (int)all->coords.height \
		&& all->map[(int)(y + p->y)][(int)p->x] < '1')
		p->y = p->y + y;
	if (x + p->x >= 0 && (int)(x + p->x) < (int)all->coords.width \
		&& all->map[(int)p->y][(int)(x + p->x)] < '1')
		p->x = p->x + x;
}

void	use_legs(t_vect vec, int neo, t_player *p, t_data *all)
{
	float	x,y;
	float	dim;

	dim = (float)1/16;
	x = p->x + neo * vec.x * (all->mov_sped + dim);
	y = p->y + neo * vec.y * (all->mov_sped + dim);
	if (y > 0 && y < all->coords.height && all->map[(int)y][(int)p->x] < '1')// wall collision
		p->y = p->y + neo * vec.y * all->mov_sped;
	if (x > 0 && x < all->coords.width && all->map[(int)p->y][(int)x] < '1')
		p->x = p->x + neo * vec.x * all->mov_sped;
}

void	use_hips(float angle, t_player *p)
{
	float oldx = p->dir.x;
	p->dir.x = p->dir.x * cos(angle) - p->dir.y *sin(angle);
	p->dir.y = oldx * sin(angle) + p->dir.y *cos(angle);
	oldx = p->plane.x;
	p->plane.x = p->plane.x * cos(angle) - p->plane.y *sin(angle);
	p->plane.y = oldx * sin(angle) + p->plane.y *cos(angle);
}

void do_stuff(t_data *all)
{
	t_player	*p;
	
	p = &all->coords.player;
	if (all->w)
		use_legs(p->dir, 1, p, all);
	if (all->s)
		use_legs(p->dir, -1, p, all);
	if (all->a)
		use_legs(p->plane, 1, p, all);
	if (all->d)
		use_legs(p->plane, -1, p, all);
	if (all->rl) // <-
		use_hips(-all->rot_sped, p);
	if (all->rr) // ->
		use_hips(all->rot_sped, p);
}

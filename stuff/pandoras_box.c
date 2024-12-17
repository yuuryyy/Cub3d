#include "cub3d_parse.h"

void	pp(int x, int y, int color, t_img *data)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = (data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

void	init_ray(t_player *p, t_ray *r, int x)
{
	float	cx;

	r->i = (int)floor(p->y);
	r->j = (int)floor(p->x);

	cx = 1 - 2 * x / (float)WIDTH;
	r->dirx = p->dir.x + p->plane.x*cx + 0.00001;
	r->diry = p->dir.y + p->plane.y*cx + 0.00001;
	
	r->delta_y = fabs(1 / r->diry);
	r->delta_x = fabs(1 / r->dirx);

	r->v_h = 0;
	r->step_j = 1 - 2*(r->dirx < 0);
	r->step_i = 1 - 2*(r->diry < 0);

	r->side_x = (float)(r->j + 1 - p->x) * r->delta_x;
	if (r->dirx < 0)
		r->side_x = (float)(p->x - r->j) * r->delta_x;

	r->side_y = (float)(r->i + 1 - p->y) * r->delta_y;
	if (r->diry < 0)
		r->side_y = (float)(p->y - r->i) * r->delta_y;

}

void	ray_dda(t_ray *r, t_player *p, t_data *all, int x)
{
	init_ray(p, r, x);
	r->hit_wall = 0;
	int		depth = 100;
	while (!r->hit_wall && depth)
	{
		depth--;
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->j += r->step_j;
			r->v_h = 0; // vertical
		}
		else
		{
			r->side_y += r->delta_y;
			r->i += r->step_i;
			r->v_h = 1; // horizontal
		}
		if (!(r->i >= 0 && r->i < (int)all->coords.height && r->j >= 0 && r->j < (int)all->coords.width))
			continue;
		else if (all->map[r->i][r->j] != '0')
			r->hit_wall = all->map[r->i][r->j];
	}
}

void	init_strip(t_strip *s, t_ray *r, t_player *p, int x)
{
	r->wall_dist = r->side_x - r->delta_x;
	if (r->v_h)
		r->wall_dist = r->side_y - r->delta_y;
	

	s->wallx = p->y + r->wall_dist * r->diry;
	if (r->v_h)
		s->wallx = p->x + r->wall_dist * r->dirx;
	
	if (x == WIDTH/2)
		x++;

	s->wallx -= floor(s->wallx);

	s->line_h = (int)(HEIGHT / r->wall_dist);
	s->start = fmax(HEIGHT / 2 - s->line_h / 2, 0);
	s->end = fmin(HEIGHT / 2 + s->line_h / 2, HEIGHT - 1);
	s->tx = (int)(s->wallx * TW);
	if ((!r->v_h && r->dirx < 0) || (r->v_h && r->diry > 0))
		s->tx = TW - s->tx - 1;
}

t_texpm pick_a_card(t_data *all, t_ray *r)
{
	if (r->v_h && r->diry > 0)
		return (all->textures->texs[1]); // south
	if (r->v_h)
		return (all->textures->texs[0]); // north wall
	if (r->dirx > 0)
		return (all->textures->texs[2]); // east
	return (all->textures->texs[3]); // west
}

int	draw_stuff(t_ray *r, t_data *all, t_player *p, int x)
{
	t_strip s;
	float step;
	int y;
	t_texpm	tex;

	tex = pick_a_card(all, r);
	init_strip(&s, r, p,x);
	step = (tex.h / (float)s.line_h);
	s.tp = (s.start - ((float)HEIGHT/2 - (float)s.line_h/2)) * step;
	y = s.start - 1;
	while (++y < s.end)
	{
		s.ty = (int)s.tp & (tex.w - 1);
		s.tp += step;
		s.color = tex.xpm.pixs[s.ty * tex.h + s.tx];
		if ((!r->v_h && r->dirx < 0) || (r->v_h && r->diry < 0)) 
			s.color += (101 << 24); //darken northen and western walls
		pp(x, y, s.color, &all->game_img);
	}
	return (y);
}

void	ray_shit(t_data *all)
{
	t_player	*p;
	t_ray		r;
	int			x;
	int			y;

	p = &all->coords.player;
	x = -1;
	while (++x < WIDTH)
	{
		ray_dda(&r, p, all, x);
		y = 0;
		if (r.hit_wall)
			y = draw_stuff(&r, all, p, x);
		while (++y < HEIGHT)
		{
			pp(x, y, 0x98585400,&all->game_img);
			int y2 = (float)HEIGHT - y;
			pp(x, y2, 0x98503030,&all->game_img);
		}
	}
	pp(WIDTH/2, HEIGHT/2, 0xFFFFFF, &all->game_img);
}

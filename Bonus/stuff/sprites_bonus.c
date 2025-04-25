/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:24:54 by achbira           #+#    #+#             */
/*   Updated: 2025/04/25 11:33:02 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	coloring2(int color, float dis)
{
	int		red;
	int		green;
	int		blue;
	float	brightness;

	brightness = 1;
	if (dis)
		brightness = fmin(1, (1.0 / dis) * 2);
	red = ((color >> 16) & 0xFF) * brightness;
	green = ((color >> 8) & 0xFF) * brightness;
	blue = (color & 0xFF) * brightness;
	return (((int)(0xff * brightness) << 24) + (red << 16) + (green << 8) + blue);
}

void	put_sprite(t_data *data, float *dists, t_sprite s, t_loaded_tex	tex)
{
	int				color;
	int				d;
	int				x;
	int				y;

	x = s.start_x - 1;
	while (++x < s.end_x)
	{
		s.tx = ((x - (s.screenx - s.w / 2)) * tex.width / s.w);
		if (s.yproj < 0 || s.yproj > dists[x])
			continue ;
		y = s.start_y - 1;
		while (++y < s.end_y)
		{
			d = y - (HEIGHT / 2 - s.h / 2);
			s.ty = (d * tex.height) / s.h;
			if (!(s.tx < 0 || s.tx > 64 || s.ty < 0 || s.ty > 64))
				color = coloring2(((int *)tex.img.addr)[s.ty * tex.width + s.tx], s.yproj);
			else
				color = 0;
			if ((color & 0x00ffff) != 0)
				pp(x, y, color, &data->game_img);
		}
	}
}

void	sprites(t_data *data, float *dists, t_player p,	t_sprite s)
{
	float		inverse;

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
	put_sprite(data, dists, s, data->s_tex[(int)data->sprite_idx]);
}

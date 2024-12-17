/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:52:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/16 23:10:54 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSE_H
# define CUB3D_PARSE_H

# include <mlx.h>
# include "../lib/Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>


# define RED   "\x1B[31m"
# define GREEN "\x1B[32m"
# define BLUE  "\x1B[34m"
# define RESET "\x1B[0m"
# define WIDTH	960
# define HEIGHT	525
# define TW 64
# define TH 64

# define ARGNUM "\tInvalid number of arguments => ./cub3d *.cub."
# define FILNAM "\tInvalid file name => ./cub3D *.cub"
# define CONFERR "\tthe configuration file is misconfigured."
# define EMPTYLN "\tthe map containts empty lines!"
# define PCONFLCT "\tA conflict in player's start position!"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		*pixs;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texpm
{
	char	*file_name;
	t_img	xpm;
	int		w;
	int		h;
}	t_texpm;

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef enum  s_position
{
	north = 1,
	south = 2,
	east = 3,
	west = 4,
}	t_position;

typedef struct s_player
{
	float		x;
	float		y;
	t_vect		dir;
	t_vect		plane;
	t_position	pos;
}	t_player;

typedef	struct s_map
{
	t_player	player;
	size_t		width;
	size_t		height;
}	t_map;

typedef struct s_textures
{
	char		*no_txtr;
	char		*so_txtr;
	char		*ea_txtr;
	char		*we_txtr;
	char		*f_color;
	char		*c_color;
	t_texpm		texs[4];
}	t_textures;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_img		game_img;

	t_textures	*textures;
	t_map		coords;
	char		**map;


	// movement
	int	w;
	int	a;
	int	s;
	int	d;
	int	rr;
	int	rl;
	float mov_sped;
	float rot_sped;
}	t_data;





// raaaaaaaaaaaaaaaaaaa
typedef struct s_strip
{
	int		line_h;
	int		start;
	int		end;
	float	wallx;
	int		tx;
	int		ty;
	float	tp;
	int		color;

}	t_strip;

typedef struct s_ray
{
	float	dirx;
	float	diry;

	float	side_x;
	float	delta_x;
	float	side_y;
	float	delta_y;

	int		i;
	int		j;
	int		step_j;
	int		step_i;

	int		v_h;
	float	wall_dist;
	int		hit_wall;
}	t_ray;

void	ray_shit(t_data *all);






int			get_textures(t_list *content, t_data *data);
t_list		*get_file_content(char *filename);
int			get_data(t_data *data, char **av);
int			check_data(t_data *data, char **av);
char		**get_map(t_list *content);
void		free_data(t_data *data);
void		free_array(char	**str);
int			array_len(char **str);
bool		is_empty(char *line);
void		free_del(void *str);
void		error(char *err);
bool		map_content_check(t_data *data, char **map);
void		rect_map(char **map, t_data *data);
t_position	player_pos(char c);
// void		path(char **map, t_map size, size_t x, size_t y);
// char		**expand_inpath(t_data *data);






int	init_data(t_data *data);
// boo
int	game_loop(void *arg);
// wingle wingle 
void do_stuff(t_data *all);

int	x_close(t_data *stuff);
int	hook_release(int keycode, t_data *stuff);
int	hook_press(int keycode, t_data *stuff);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:52:16 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/23 18:06:59 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSE_H
# define CUB3D_PARSE_H

# include "../lib/Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>


# define RED   "\x1B[31m"
# define GREEN "\x1B[32m"
# define BLUE  "\x1B[34m"
# define RESET "\x1B[0m"
# define WIDTH	1920
# define HEIGHT	1080

# define ARGNUM "\tInvalid number of arguments => ./cub3d *.cub."
# define FILNAM "\tInvalid file name => ./cub3D *.cub"
# define CONFERR "\tthe configuration file is misconfigured."
# define EMPTYLN "\tthe map containts empty lines!"
# define PCONFLCT "\tA conflict in player's start position!"


# define BASE_SPEED 0.06
# define BASE_ROTATION_SPEED 0.07


# define TILE_WIDTH 24

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		*pixs;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vect
{
	float	x;
	float	y;
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
}	t_textures;


typedef	struct s_colors
{
	int	f_color;
	int	c_color;
}	t_colors;


typedef struct s_controller
{
	// movement
	int	w;
	int	a;
	int	s;
	int	d;
	int	rr;
	int	rl;
	float mov_sped;
	float rot_sped;	
}	t_controller;

// raaaaaaaaaaaaaaaaaaa
typedef struct s_ray
{
	t_vect	dir;

	t_vect	side;
	t_vect	delta;

	t_vect	step;
	int		map_y;
	int		map_x;

	int		v_h;
	float	wall_dist;
	float	wall_x;
	int		hit_wall;

	int		line_h;
	int		start;
	int		end;
	unsigned int	color;
}	t_ray;


typedef struct s_loaded_tex
{
	t_img	img;
	int		width;
	int		height;

}	t_loaded_tex;


typedef struct s_ready_tex
{
	t_loaded_tex	no_txtr;
	t_loaded_tex	so_txtr;
	t_loaded_tex	ea_txtr;
	t_loaded_tex	we_txtr;

}	t_ready_tex;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_img		game_img;
	
	char		**map;
	t_map		coords;
	t_controller move;
	
	t_textures	*textures;
	t_colors	colors;
	t_ready_tex	ready_tex;
}	t_data;

void		create_world(t_data *all);
t_loaded_tex *get_texture(t_data *data, t_ray *ray);
void		load_all_textures(t_ready_tex *textures, void *mlx, t_data *data);
int			build_wall_stripe(t_ray *r, t_data *all, int x);
void	pp(int x, int y, int color, t_img *data);

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


int		init_data(t_data *data);
int		game_loop(void *arg);
void	move_player(t_data *all);
int		x_exit(t_data *data);
int		key_release_hook(int keycode, t_data *data);
int		key_press_hook(int keycode, t_data *data);

#endif
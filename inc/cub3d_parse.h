/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:52:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/15 22:50:40 by ychagri          ###   ########.fr       */
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


# define RED   "\x1B[31m"
# define GREEN "\x1B[32m"
# define BLUE  "\x1B[34m"
# define RESET "\x1B[0m"

# define ARGNUM "\tInvalid number of arguments => ./cub3d *.cub."
# define FILNAM "\tInvalid file name => ./cub3D *.cub"
# define CONFERR "\tthe configuration file is misconfigured."
# define EMPTYLN "\tthe map containts empty lines!"
# define PCONFLCT "\tA conflict in player's start position!"

typedef enum  s_position
{
	north = 1,
	south = 2,
	east = 3,
	west = 4,
}	t_position;

typedef struct s_player
{
	int			x;
	int			y;
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
	char		*we_txtr;
	char		*ea_txtr;
	char		*f_color;
	char		*c_color;
}	t_textures;

typedef struct s_data
{
	t_textures	*textures;
	t_map		coords;
	char		**map;
}	t_data;

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

#endif
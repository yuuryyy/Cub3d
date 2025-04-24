/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_header.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:22:23 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/24 21:24:34 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_HEADER_H
# define G_HEADER_H

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
# define CE "\tthe configuration file is misconfigured."
# define EMPTYLN "\tthe map containts empty lines!"
# define PCONFLCT "\tA conflict in player's start position!"
# define CHARR "\tInvalid characters !!"
# define OPNMP "\tUnclosed map!"

#define SO "SO "
#define NO "NO "
#define WE "WE "
#define EA "EA "
#define F "F "
#define C "C "
#define SOT "SO\t"
#define NOT "NO\t"
#define WET "WE\t"
#define EAT "EA\t"
#define FT "F\t"
#define CT "C\t"

# define BASE_SPEED 0.06
# define BASE_ROTATION_SPEED 0.07

# define TILE_WIDTH 24

#endif
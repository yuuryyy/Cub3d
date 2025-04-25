/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_header.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:22:23 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/25 23:19:43 by ychagri          ###   ########.fr       */
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

# define FIRE00         "textures/fire/fire00.xpm"
# define FIRE01         "textures/fire/fire01.xpm"
# define FIRE02         "textures/fire/fire02.xpm"
# define FIRE03         "textures/fire/fire03.xpm"
# define FIRE04         "textures/fire/fire04.xpm"
# define FIRE05         "textures/fire/fire05.xpm"
# define FIRE06         "textures/fire/fire06.xpm"
# define FIRE07         "textures/fire/fire07.xpm"
# define FIRE08         "textures/fire/fire08.xpm"
# define FIRE09         "textures/fire/fire09.xpm"
# define FIRE10         "textures/fire/fire10.xpm"
# define FIRE11         "textures/fire/fire11.xpm"
# define FIRE12         "textures/fire/fire12.xpm"
# define FIRE13         "textures/fire/fire13.xpm"
# define FIRE14         "textures/fire/fire14.xpm"
# define FIRE15         "textures/fire/fire15.xpm"
# define FIRE16         "textures/fire/fire16.xpm"
# define FIRE17         "textures/fire/fire17.xpm"
# define FIRE18         "textures/fire/fire18.xpm"

# define PORTAL00       "textures/portal/portal00.xpm"
# define PORTAL01       "textures/portal/portal01.xpm"
# define PORTAL02       "textures/portal/portal02.xpm"
# define PORTAL03       "textures/portal/portal03.xpm"
# define PORTAL04       "textures/portal/portal04.xpm"
# define PORTAL05       "textures/portal/portal05.xpm"
# define PORTAL06       "textures/portal/portal06.xpm"
# define PORTAL07       "textures/portal/portal07.xpm"
# define PORTAL08       "textures/portal/portal08.xpm"
# define PORTAL09       "textures/portal/portal09.xpm"
# define PORTAL10       "textures/portal/portal10.xpm"
# define PORTAL11       "textures/portal/portal11.xpm"
# define PORTAL12       "textures/portal/portal12.xpm"
# define PORTAL13       "textures/portal/portal13.xpm"
# define PORTAL14       "textures/portal/portal14.xpm"
# define PORTAL15       "textures/portal/portal15.xpm"
# define PORTAL16       "textures/portal/portal16.xpm"
# define PORTAL17       "textures/portal/portal17.xpm"
# define PORTAL18       "textures/portal/portal18.xpm"

# define RED            "\x1B[31m"
# define GREEN          "\x1B[32m"
# define BLUE           "\x1B[34m"
# define RESET          "\x1B[0m"
# define WIDTH	        1920
# define HEIGHT	        1080

# define ARGNUM         "\tInvalid number of arguments => ./cub3d *.cub."
# define FILNAM         "\tInvalid file name => ./cub3D *.cub"
# define CE             "\tthe configuration file is misconfigured."
# define EMPTYLN        "\tthe map containts empty lines!"
# define PCONFLCT       "\tA conflict in player's start position!"
# define CHARR          "\tInvalid characters !!"
# define OPNMP          "\tUnclosed map!"
# define MALOC          "\tMemory allocation error!"

# define SO             "SO "
# define NO             "NO "
# define WE             "WE "
# define EA             "EA "
# define F              "F "
# define C              "C "
# define SOT            "SO\t"
# define NOT            "NO\t"
# define WET            "WE\t"
# define EAT            "EA\t"
# define FT             "F\t"
# define CT             "C\t"

# define BASE_SPEED 0.06
# define BASE_ROTATION_SPEED 0.07

# define TILE_WIDTH 24

#endif
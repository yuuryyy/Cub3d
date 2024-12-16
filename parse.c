/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:52:08 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/15 22:54:57 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"



int main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ac != 2)
		return (error(ARGNUM), 1);
	if(check_data(&data, av))
		return (1);
	// printf("%s\n", data.textures->c_color);
	// printf("%s\n", data.textures->f_color);
	// printf("%s\n", data.textures->we_txtr);
	// printf("%s\n", data.textures->so_txtr);
	// printf("%s\n", data.textures->ea_txtr);
	// printf("%s\n", data.textures->no_txtr);
	// for(int i = 0; data.map[i]; i++)
	// 	printf("|%s|\n", data.map[i]);
	// printf("vdfdfvdfv\n");
	free_data(&data);
	// while (1)
	// {
	// 	;
	// }
	//check file content;
	//check map chars 
	//get map and texts plyr pos width height...

}
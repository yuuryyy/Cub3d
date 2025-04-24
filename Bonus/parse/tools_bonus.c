/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:57:26 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/24 19:08:23 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_array(char	**str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	array_len(char **str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_del(void *str)
{
	if (str)
		free(str);
	str = NULL;
}

t_position	player_pos(char c)
{
	if (c == 'W')
		return (west);
	else if (c == 'S')
		return (south);
	else if (c == 'N')
		return (north);
	else if (c == 'E')
		return (east);
	return (0);
}

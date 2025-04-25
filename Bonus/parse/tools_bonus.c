/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 04:57:26 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/25 22:45:31 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	add_sprite(int i, int k, t_data *data)
{
	t_sprite	*sprite;
	t_list		*new;

	if (data->map[i][k] != '4')
		return (1);
	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		return (error(MALOC), x_exit(data), 0);
	new = ft_lstnew(sprite);
	if (!new)
		return (free(sprite), x_exit(data), 0);
	ft_lstadd_back(&data->sprite, new);
	sprite->x = k + 0.5;
	sprite->y = i + 0.5;
	data->map[i][k] = '0';
	return (1);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achbira <achbira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:03:27 by ychagri           #+#    #+#             */
/*   Updated: 2025/04/15 18:15:38 by achbira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	error(char *err)
{
	ft_putstr_fd(RED"ERROR :\n"BLUE, 2);
	ft_putendl_fd(err, 2);
	ft_putstr_fd(RESET, 2);
}

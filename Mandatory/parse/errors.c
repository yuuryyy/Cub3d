/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:03:27 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/04 00:26:47 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	error(char *err)
{
	ft_putstr_fd(RED"ERROR :\n"BLUE, 2);
	ft_putendl_fd(err, 2);
	ft_putstr_fd(RESET, 2);
}

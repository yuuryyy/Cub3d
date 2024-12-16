/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:14:16 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/15 19:32:41 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		total_s;
	void		*memory;

	total_s = count * size;
	memory = malloc(total_s);
	if (!memory)
		return (NULL);
	ft_bzero(memory, total_s);
	return (memory);
}

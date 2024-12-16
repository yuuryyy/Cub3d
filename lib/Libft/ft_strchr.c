/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:59:28 by ychagri           #+#    #+#             */
/*   Updated: 2024/12/03 19:52:43 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c, int t)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c || s[i] == (char)t)
			return ((char *)(s + i));
		i++;
	}
	if (!(char)c == !s[i])
		return ((char *)(s + i));
	return (0);
}

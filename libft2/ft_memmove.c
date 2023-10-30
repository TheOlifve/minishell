/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:48:53 by rugrigor          #+#    #+#             */
/*   Updated: 2023/02/01 11:49:25 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str, const void *dest, size_t n)
{
	unsigned char	*str1;
	unsigned char	*dest1;
	size_t			i;

	str1 = (unsigned char *) str;
	dest1 = (unsigned char *) dest;
	if (!dest1 || !str1)
		return (0);
	if (dest && str && dest1 < str1)
	{
		while (n != 0)
		{
			n--;
			str1[n] = dest1[n];
		}
	}
	else
	{
		i = -1;
		while (++i < n)
			str1[i] = dest1[i];
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:13:05 by rugrigor          #+#    #+#             */
/*   Updated: 2023/02/01 11:48:48 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str, const void *dest, size_t n)
{
	unsigned char	*dest1;
	unsigned char	*str1;
	size_t			i;

	i = 0;
	dest1 = (unsigned char *) dest;
	str1 = (unsigned char *) str;
	if (!str1)
		return (0);
	while (dest1 && str1 && i < n)
	{
		str1[i] = dest1[i];
		i++;
	}
	return (str);
}

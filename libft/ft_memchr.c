/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:27:57 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 14:25:56 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*ptr;
	size_t		i;

	i = 0;
	ptr = (const char *) str;
	if (!str)
		return (0);
	while (i < n)
	{
		if (*ptr == (char)c)
			return ((void *)ptr);
		ptr++;
		i++;
	}
	return (0);
}

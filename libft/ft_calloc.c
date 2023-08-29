/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:54:21 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 14:41:09 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t p, size_t n)
{
	size_t			i;
	void			*ptr;

	i = p * n;
	if (p && n)
	{
		if ((i < n || i < p))
			return (NULL);
	}
	ptr = (void *)malloc(i);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, i);
	return (ptr);
}

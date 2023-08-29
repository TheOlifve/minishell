/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:42:45 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 14:52:10 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *str, size_t destn)
{
	size_t	str1;
	size_t	i;
	size_t	n;
	size_t	x;

	i = 0;
	str1 = ft_strlen((char *)str);
	n = ft_strlen(dest);
	x = n;
	if (dest == NULL && str == NULL)
		return (0);
	if (destn <= n || destn == 0)
		return (destn + str1);
	while (str && str[i] && n + 1 < destn)
		dest[n++] = str[i++];
	dest[n] = '\0';
	return (x + str1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:33:42 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 14:34:56 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *str, size_t destn)
{
	size_t	i;

	i = 0;
	if (!str || !dest)
		return (0);
	while (i + 1 < destn && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	if (destn != 0)
		dest[i] = '\0';
	return (ft_strlen((char *)str));
}

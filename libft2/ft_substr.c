/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:58:10 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 15:14:42 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*s1;
	size_t	n;

	n = 0;
	s1 = (char *) s;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	if (len == 0 || ft_strlen(s1) < len || ft_strlen(s1) < start)
	{
		ptr[n] = '\0';
		return (ptr);
	}
	while (s1 && n < len)
		ptr[n++] = s1[start++];
	ptr[n] = '\0';
	return (ptr);
}

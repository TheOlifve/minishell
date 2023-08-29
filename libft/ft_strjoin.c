/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:25:27 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/21 12:13:39 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	a;
	size_t	b;
	size_t	i;
	size_t	n;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	i = 0;
	n = 0;
	ptr = (char *)malloc(sizeof(char) * (a + b + 1));
	if (s1 == 0 || s2 == 0 || ptr == 0)
		return (0);
	while (i < a)
		ptr[n++] = s1[i++];
	i = 0;
	while (i < b)
		ptr[n++] = s2[i++];
	ptr[n] = '\0';
	return (ptr);
}

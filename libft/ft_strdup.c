/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:56:06 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 15:14:04 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*p;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	p = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (str && str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

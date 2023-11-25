/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:38:14 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 13:51:49 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *ptr, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *) ptr;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)n)
			return (&str[i]);
		i--;
	}
	return (0);
}

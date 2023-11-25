/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:29:49 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/31 13:51:06 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int n)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if ((char)n == '\0')
		return (&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char)n)
			return (&str[i]);
		i++;
	}
	return (0);
}

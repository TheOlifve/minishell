/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:45:10 by rugrigor          #+#    #+#             */
/*   Updated: 2023/01/27 19:38:49 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen1(int str)
{
	size_t	i;

	i = 0;
	if (str == 0)
		return (1);
	while (str)
	{
		str = str / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	size_t	x;
	long	num;

	num = n;
	i = ft_strlen1(num);
	x = 0;
	if (n < 0)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (num < 0)
	{
		str[0] = '-';
		num = num * -1;
		x = 1;
	}
	str[i] = '\0';
	while (i-- > x)
	{
		str[i] = 48 + (num % 10);
		num = num / 10;
	}
	return (str);
}

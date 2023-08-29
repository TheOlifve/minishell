/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:36:58 by rugrigor          #+#    #+#             */
/*   Updated: 2023/04/20 14:37:19 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	unsigned char	*str1;
	long			neg;
	long			num;

	neg = 1;
	if (!str)
		return (0);
	str1 = (unsigned char *) str;
	while (((*str1 >= 9 && *str1 <= 13) || *str1 == ' '))
		str1++;
	if (*str1 == '-' || *str1 == '+')
	{
		if (*str1 == '-')
			neg = -neg;
		str1++;
	}
	if (*str1 < 48 && *str1 > 57)
		return (0);
	num = 0;
	while (*str1 >= 48 && *str1 <= 57)
	{
		num = num * 10 + (*str1 - 48);
		str1++;
	}
	return (num * neg);
}

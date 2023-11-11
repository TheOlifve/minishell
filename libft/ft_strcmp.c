/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:07:44 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/11 23:57:19 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	if (ft_strcmp(s2, "\n") == -10)
		return(0);
	i = ft_strlen(s2);
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		i--;
		s1++;
		s2++;
	}
	if (i == 0)
		return (-10);
	return (0);
}

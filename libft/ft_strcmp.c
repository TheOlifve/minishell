/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:07:44 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/11 14:03:38 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_ast(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '*')
		i++;
	return (i);
}

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
		return (0);
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

int	ft_strcmp3(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	if (s1[i] - s2[j] >= 0 && ft_strlen(s1) >= ft_strlen(s2))
		return (s1[i] - s2[j]);
	return (-1);
}

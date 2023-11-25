/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:38:14 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/27 12:49:05 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ast(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '*')
		i++;
	return (i);
}

int	ft_check(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (str && str[i] && str[i] != '*')
		i++;
	if (j == i + 1)
		return (0);
	return (1);
}

int	ftcheck(char *str, char *cmp, int size)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (size > len)
		return (1);
	while (str[i] && cmp[i] && i < size)
	{
		if (str[i] != cmp[i])
			return (1);
		i++;
	}
	return (0);
}

int	bkcheck(char *str, char *cmp, int k)
{
	int	i;
	int	j;

	i = ft_strlen(cmp) - 1;
	j = ft_strlen(str) - 1;
	if (j < i)
		return (1);
	while (i > k)
	{
		if (str[j] != cmp[i])
			return (1);
		i--;
		j--;
	}
	return (0);
}

int	ft_strrcmp(char *st, char *cmp)
{
	int		i;
	int		j;
	char	*str;

	i = ft_ast(cmp);
	j = ft_check(cmp);
	str = ft_strtrim(st, "\n");
	if (i == 0)
		return (bkcheck(str, cmp, i));
	else if (j == 0)
		return (ftcheck(str, cmp, i));
	else
	{
		if (ftcheck(str, cmp, i) == 0
			&& bkcheck(str, cmp, i) == 0)
			return (0);
		else
			return (1);
	}
	return (0);
}

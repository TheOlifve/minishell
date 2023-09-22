/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 3223/07/10 14:44:13 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/19 00:16:13 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_join2(t_ms *ms, int i, char c, int n)
{
	char	*str1;
	char	*str2;
	int		x;

	x = i;
	if (n == 0)
		while (ms->args_old[x++] == c)
				n++;
	str1 = ft_substr(ms->args_old, 0, i);
	str2 = ft_substr(ms->args_old,
			i + n, ft_strlen(ms->args_old) - (i + n));
	free(ms->args_old);
	ms->args_old = ft_strjoin(str1, str2);
	ms->num--;
	if (c == 34)
		ms->c1 = ms->c1 + (n - 1);
	else if (c == 39)
		ms->c2 = ms->c2 + (n - 1);
	return (n);
}

int	str_join(t_ms *ms, int i, char c) 
{
	if (c == 39 && ms->c1 % 2 == 0)
		while (ms->args_old && ms->args_old[++i])
		{
			if (ms->args_old[i] == 32)
				ms->args_old[i] = 5;
			else if (ms->args_old[i] == '\t')
				ms->args_old[i] = 4;
			if (ms->args_old[i] == 39)
			{
				ms->num = ms->num - str_join2(ms, ms->x, 39, 1);
				i--;
				ms->num = ms->num - str_join2(ms, i, 39, 1);
				ms->c2++;
				return (ms->x - i + 1);
			}
		}
	i = ms->x;
	if (c == 34 && ms->c2 % 2 != 0)
		return (0);
	else if (c == 39 && ms->c1 % 2 != 0)
		return (0);
	else
		ms->num = ms->num - str_join2(ms, i, c, 0);
	return (1);
}

int	simbol2(t_ms *ms, int i)
{
	if (ms->args_old[i] && ms->args_old[i] == 34 && ms->c2 %2 != 0)
	{
		while (ms && ms->args_old && ms->args_old[++i])
		{
			if (ms->args_old[i] == 34)
				return (i);
			else if (ms->args_old[i] == 39)
				return (i);
		}
			
	}
	else if (ms->args_old[i] && ms->args_old[i] == 39 && ms->c1 %2 != 0)
	{
		while (ms && ms->args_old && ms->args_old[++i])
		{
			if (ms->args_old[i] == 39)
				return (1);
			else if (ms->args_old[i] == 34)
				return (2);
		}
			
	}
	return (0);
}

int	simbol(t_ms *ms, int i)
{
	while (++i < ms->num)
	{
		if (ms->args_old[i] == 34 && (ms->c1 %2 != 0 || simbol2(ms, i) != 2))
			ms->c1++;
		if (ms->args_old[i] == 39 && (ms->c2 %2 != 0 || simbol2(ms, i) != 2))
			ms->c2++;
		if (ms->args_old[i] == 32 && (ms->c2 % 2 != 0 || ms->c1 % 2 != 0))
			ms->args_old[i] = 5;
		if (ms->args_old[i] == '\t' && (ms->c2 % 2 != 0 || ms->c1 % 2 != 0))
			ms->args_old[i] = 4;
		ms->x = i;
		if (ms->args_old[i] == 39 && (ms->c2 %2 != 0 || simbol2(ms, i) != 2))
			i -= str_join(ms, i, 39);
		else if (ms->args_old[i] == 34 && (ms->c1 %2 != 0 || simbol2(ms, i) != 2))
			i -= str_join(ms, i, 34);
		if (ms->args_old[i] == 36)
			i = dol_prep(ms, i, -1, 0);
	}
	if (ms->c1 % 2 != 0 || ms->c2 % 2 != 0)
		return (1);
	ms->args = ms->args_old;
	return (0);
}

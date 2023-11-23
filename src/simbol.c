/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 3223/07/10 14:44:13 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/23 14:04:01 by hrahovha         ###   ########.fr       */
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
	free(str1);
	free(str2);
	return (n);
}

int	str_join(t_ms *ms, int i, char c)
{
	ms->x = i;
	if ((c == 39 && ms->args_old[i + 1] != 39 && ms->c1 % 2 == 0)
		|| (c == 34 && ms->args_old[i + 1] != 34 && ms->c2 % 2 == 0))
	{
		while (ms->args_old && ms->args_old[++i])
		{
			i = tabzz(ms, i, c);
			if (ms->args_old[i] == c)
			{
				ms->num = ms->num - str_join2(ms, ms->x, c, 1);
				i--;
				ms->num = ms->num - str_join2(ms, i, c, 1);
				if (c == 39)
					ms->c2++;
				else
					ms->c1++;
				return (ms->x - i + 1);
			}
		}
	}
	if ((c == 34 && ms->c2 % 2 != 0) || (c == 39 && ms->c1 % 2 != 0))
		return (0);
	else
		ms->num = ms->num - str_join2(ms, ms->x, c, 0);
	return (0);
}

int	simbol2(t_ms *ms, int i)
{

	if (ms->args_old[i] && ms->args_old[i] == 34 && ms->c2 % 2 != 0)
	{
		while (ms && ms->args_old && ms->args_old[++i])
		{
			if (ms->args_old[i] == 34)
				return (i);
			else if (ms->args_old[i] == 39)
				return (i);
		}	
	}
	else if (ms->args_old[i] && ms->args_old[i] == 39 && ms->c1 % 2 != 0)
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

int	o_space(t_ms *ms, int i)
{
	if ((ms->args_old[i] == '>' && ms->args_old[i + 1] == '>')
		|| (ms->args_old[i] == '<' && ms->args_old[i + 1] == '<')
		|| (ms->args_old[i] == '|' && ms->args_old[i + 1] == '|')
		|| (ms->args_old[i] == '&' && ms->args_old[i + 1] == '&')
		|| (i != 0 && ms->args_old[i] == '>' && ms->args_old[i - 1] != '>')
		|| (i != 0 && ms->args_old[i] == '<' && ms->args_old[i - 1] != '<')
		|| ms->args_old[i] == '|')
		if (i != 0 && ms->args_old[i - 1] != 32)
			return (o_space2(ms, i, 0) - 1);
	if ((ms->args_old[i] == '|' && ms->args_old[i + 1] == '|')
		|| (ms->args_old[i] == '&' && ms->args_old[i + 1] == '&'))
		if (ms->args_old[i + 2] != 32)
			return (o_space2(ms, i, 2));
	if (ms->args_old[i] == '|' || ms->args_old[i] == ')')
		if ((ms->args_old[i + 1] != 32 && ms->args_old[i] == '|')
			|| (ms->args_old[i] == ')' && ms->args_old[i - 1] == 32))
			return (o_space2(ms, i, 1));
	if ((ms->args_old[i] == '>' && ms->args_old[i + 1] == '>')
		|| (ms->args_old[i] == '<' && ms->args_old[i + 1] == '<'))
		if (ms->args_old[i + 2] == 32)
			return (o_space3(ms, i, 2));
	if (ms->args_old[i] == 60 || ms->args_old[i] == 62 || ms->args_old[i] == 40)
		if (ms->args_old[i + 1] == 32)
			return (o_space3(ms, i, 1));
	return (0);
}

int	simbol(t_ms *ms, int i)
{
	while (++i < ms->num)
	{
		if (ms->args_old[i] == 34 && (ms->c1 % 2 != 0 || simbol2(ms, i) != 2))
			ms->c1++;
		if (ms->args_old[i] == 39 && (ms->c2 % 2 != 0 || simbol2(ms, i) != 2))
			ms->c2++;
		if (ms->args_old[i] == 32 && (ms->c2 % 2 != 0 || ms->c1 % 2 != 0))
			ms->args_old[i] = 5;
		if (ms->args_old[i] == '\t' && (ms->c2 % 2 != 0 || ms->c1 % 2 != 0))
			ms->args_old[i] = 4;
		if (ms->args_old[i] == 39 && (ms->c2 % 2 != 0 || simbol2(ms, i) != 2))
			i -= str_join(ms, i, 39);
		else if (ms->args_old[i] == 34 && (ms->c1 % 2 != 0
				|| simbol2(ms, i) != 2))
			i -= str_join(ms, i, 34);
		if (ms->args_old[i] == 36 && (!(i > 1 && ms->args_old[i - 1] == '<'
					&& ms->args_old[i - 2] == '<')))
			i = dol_prep(ms, i, -1, 0);
		i += o_space(ms, i);
		if (ms->args_old[i] == ';')
			ms->args_old[i] = 32;
	}
	if (ms->c1 % 2 != 0 || ms->c2 % 2 != 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simbol2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:12:25 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/24 00:21:27 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_join2(t_ms *ms, int i, char c, int n)
{
	char	*str1;
	char	*str2;
	int		x;

	x = i;
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

int	chak(t_ms *ms, int i)
{
	while (ms->args_old[++i])
	{
		if (ms->args_old[i] == 34 && ms->c1 != 0)
			return (1);
		else if (ms->args_old[i] == 39 && ms->c2 != 0)
			return (1);
	}
	return (0);
}

int	hate(t_ms *ms, int i, int n)
{
	while (ms->args_old[++i])
	{
		if (ms->args_old[i] == n)
			return (1);
	}
	return (0);
}

void	path(t_ms *ms, int i, int n)
{
	ms->n = 0;
	if (hate(ms, i, n) != 0)
	{
		while (ms->args_old[++i] != n)
		{
			if (ms->args_old[i] == 32 || ms->args_old[i] == '\t')
					ms->n++;
		}
	}
}

int	str_join(t_ms *ms, int i, char c)
{
	ms->x = i;
	if (c == 34 && ms->c2 % 2 != 0)
		;
	else if (c == 39 && ms->c1 % 2 != 0)
		;
	else
		return (str_join2(ms, i, c, 0));
	return (0);
}

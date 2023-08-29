/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 3223/07/10 14:44:13 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/24 11:43:22 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	probel3(t_ms *ms, int i)
{
	while (i-- != ms->x)
	{
		if (ms->args_old[i] == 5 || ms->args_old[i] == 32
			|| ms->args_old[i] == '\t' || ms->args_old[i] == 4)
			;
		else
			return (1);
	}
	return (0);
}

int	probel2(t_ms *ms, int i)
{
	while (ms->args_old[++i] != 39)
	{
		if (ms->args_old[i] == 32 || ms->args_old[i] == '\t')
			;
		else
		{
			path(ms, i, 39);
			return (1);
		}
	}
	if (probel3(ms, i) != 0)
		return (1);
	return (0);
}

int	probel(t_ms *ms, int i)
{
	if (ms->c1 != 0 && ms->c1 % 2 == 0)
	{
		while (ms->args_old[++i] != 34)
		{
			if (ms->args_old[i] == 32 || ms->args_old[i] == '\t')
				;
			else
			{
				path(ms, i, 34);
				return (1);
			}
		}
		if (probel3(ms, i) != 0)
			return (1);
	}
	else if (ms->c2 != 0 && ms->c2 % 2 == 0)
	{
		if (probel2(ms, i) != 0)
			return (1);
	}
	return (0);
}

void	simbol2(t_ms *ms, int i, char c)
{
	if (c == 32)
	{
		if (probel(ms, i) != 0)
		{
			ms->args_old[i] = 5;
		}
		else if (ms->n > 0)
		{
			ms->n--;
			ms->args_old[i] = 5;
		}
	}
	else if (c == '\t')
	{
		if (probel(ms, i) != 0)
			ms->args_old[i] = 4;
		else if (ms->n > 0)
		{
			ms->n--;
			ms->args_old[i] = 4;
		}
	}
}

int	simbol(t_ms *ms, int i)
{
	while (++i < ms->num)
	{
		if (ms->args_old[i] == 34)
			ms->c1++;
		if (ms->args_old[i] == 39)
			ms->c2++;
		if (ms->args_old[i] == 32 && (ms->c2 % 2 != 0 || ms->c1 % 2 != 0))
			ms->args_old[i] = 5;
		if (ms->args_old[i] == '\t' && (ms->c2 % 2 != 0 || ms->c1 % 2 != 0))
			ms->args_old[i] = 4;
		if (ms->args_old[i] == 32 && (ms->c2 % 2 == 0 || ms->c1 % 2 == 0)
			&& chak(ms, i) != 0)
			simbol2(ms, i, 32);
		if (ms->args_old[i] == '\t' && (ms->c2 % 2 == 0 || ms->c1 % 2 == 0)
			&& chak(ms, i) != 0)
			simbol2(ms, i, '\t');
		if (ms->args_old[i] == 39)
			i -= str_join(ms, i, 39);
		else if (ms->args_old[i] == 34)
			i -= str_join(ms, i, 34);
	}
	if (ms->c1 % 2 != 0 || ms->c2 % 2 != 0)
		return (1);
	ms->args = ms->args_old;
	return (0);
}

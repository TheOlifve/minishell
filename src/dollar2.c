/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:39:01 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/08 14:00:14 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dol2(char *ptr, char *str, int i, int n)
{
	i++;
	ptr = malloc(sizeof(char) * (dol_count(str, i)));
	if (!ptr)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] == 36)
			break ;
		ptr[n++] = str[i++];
	}
	ptr[n] = '\0';
	return (ptr);
}

char	*trim_dol(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = -1;
	while (str && str[i++] != '$')
		;
	tmp = malloc(i * sizeof(char));
	while (++j < i)
		tmp[j] = str[j];
	tmp[j - 1] = '\0';
	return (tmp);
}

void	check_dol2(t_ms *ms, int i, int j)
{
	char	*tmp;

	ms->str[i][j] = 32;
	while (ms->str[i][++j] != 39)
		;
	ms->str[i][j] = 32;
	tmp = ft_strdup(ms->str[i]);
	free(ms->str[i]);
	ms->str[i] = ft_strtrim(tmp, " ");
	free(tmp);
}

char	*dol_helper(t_ms *ms, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = dol_check(ms, ms->str[i]);
	tmp2 = trim_dol(ms->str[i]);
	free(ms->str[i]);
	ms->str[i] = ft_strjoin2(tmp2, tmp);
	return (tmp);
}

void	check_dol(t_ms *ms, int	i, int j)
{
	char	*tmp;

	while (ms && ms->str && ms->str[i])
	{
		j = 0;
		while (ms->str && ms->str[i] && ms->str[i][j])
		{
			if (ms->str[i][j] == 39 && ms->str[i][j + 1]
				&& ms->str[i][j + 1] == '$')
			{
				check_dol2(ms, i, j);
				break ;
			}
			else if (ms->str[i][j] == '$')
			{
				tmp = dol_helper(ms, i);
				if (tmp[0] == '$')
					break ;
				j--;
			}
			j++;
		}
		i++;
	}
}
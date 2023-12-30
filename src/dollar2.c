/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:39:01 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/22 11:56:15 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isit(t_ms *ms, char i, int n)
{
	if (i == 34 || i == 39 || i == 46 || i == 33 || i == 35 || i == 37
		|| i == 40 || i == 41 || i == 43 || i == 44 || i == 45 || i == 47
		|| i == 59 || i == 58 || i == 64 || i == 91 || i == 93 || i == 36
		|| i == 94 || i == 123 || i == 125 || i == 124 || i == 126
		|| i == 32 || i == '\t' || (n == ms->dol2 + 2
			&& ft_isdigit(ms->args_old[ms->dol2 + 2]) == 1
			&& ft_isdigit(ms->args_old[ms->dol2 + 1]) == 1) || i == '='
		|| (n > 0 && ms->args_old[n - 1] == 42)
		|| (n > 0 && ms->args_old[n - 1] == 92))
		return (1);
	return (0);
}

int	dol_prep2(t_ms *ms, char *ptr, int x, int i)
{
	char	*tmp;
	char	*tmp2;
	int		y;

	if (x == 1 && ptr[0] == '$' && ptr[1] == '\0')
		tmp = ft_strdup("$");
	else
		tmp = dol_check(ms, ptr);
	y = ft_strlen(tmp);
	ms->num = ms->num - ft_strlen(ptr) + ft_strlen(tmp);
	free(ptr);
	tmp2 = ft_substr(ms->args_old, 0, ms->dol2);
	ptr = ft_strjoin2(tmp2, tmp);
	free(tmp);
	free(tmp2);
	tmp = ft_substr(ms->args_old, i, ft_strlen(ms->args_old));
	free(ms->args_old);
	ms->args_old = ft_strjoin2(ptr, tmp);
	free(ptr);
	free(tmp);
	return (y);
}

int	dol_prep(t_ms *ms, int i, int x, int y)
{
	char	*ptr;
	int		n;

	n = 0;
	ms->dol2 = i;
	y = ms->dol2;
	while (ms->args_old && ms->args_old[++i])
		if (ft_isit(ms, ms->args_old[i], i) == 1)
			break ;
	if ((ms->args_old[i - 1] == 36 && (ms->args_old[i] == 34
				|| ms->args_old[i] == 39)))
	{
		dol_prep4(ms, i, NULL, NULL);
		return (ms->dol2 - 1);
	}
	ptr = malloc(sizeof(char) * (i - ms->dol2 + 1));
	while (ms && ms->args_old && ++x != (i - ms->dol2))
		ptr[x] = ms->args_old[y++];
	ptr[x] = '\0';
	y = dol_prep2(ms, ptr, x, i);
	i = ms->dol2;
	while (ms->args_old && ms->args_old[i] && ms->args_old[i++] == 36)
		n++;
	return (ms->dol2 + y + n - 1);
}

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

int	tabzz(t_ms *ms, int i, int c)
{
	ms->user = 0;
	if (ms->args_old[i] == 32)
		ms->args_old[i] = 5;
	else if (ms->args_old[i] == '\t')
		ms->args_old[i] = 4;
	if (ms->args_old[i] == 36 && c == 34
		&& (!(i > 2 && ms->args_old[i - 2] == '<'
				&& ms->args_old[i - 3] == '<')))
		return (dol_prep(ms, i, -1, 0));
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/07/27 13:30:59 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var1(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if ((str[0] > 64 && str[0] < 91)
			|| (str[0] > 96 && str[0] < 123)
				|| (str[0] == '_'))
		;
	else
		return (ERR("unset", str));
	while (str && str[i])
	{
		if (((str[i] > 64 && str[i] < 91)
				|| (str[i] > 96 && str[i] < 123)
				|| (str[i] > 47 && str[i] < 58))
				|| str[i] == '_')
				i++;
		else
			return (ERR("unset", str));
	}
	return (0);
}

int	ft_remove(t_ms *ms, int pos, char **tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ms->cache && ms->cache[i])
		i++;
	free(ms->cache);
	ms->cache = malloc(sizeof(char *) * i);
	ms->cache[i - 1] = NULL;
	i = 0;
	while (tmp && tmp[j] && ms->cache[i])
	{
		if (j != pos)
		{
			ms->cache[i] = tmp[j];
			i++;
			j++;
		}
		else
			j++;
	}
	return (0);
}

int	ft_unset(t_ms *ms, char *str)
{
	int		i;
	char	*str2;
	char	**tmp;

	if (check_var1(str) == 0)
		;
	else
		return (1);
	i = 0;
	if (!ms->cache)
		return (1);
	str2 = ft_strdup(str);
	str = ft_strjoin(str2, "=");
	free(str2);
	tmp = caching(ms->cache);
	while (tmp && tmp[i])
	{
		if (ft_strncmp(tmp[i], str, ft_strlen(str)) == 0)
			ft_remove(ms, i, tmp);
		i++;
	}
	free(str);
	return (0);
}

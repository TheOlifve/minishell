/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/12/20 14:36:36 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append(t_ms *ms, int len, char *str, char **tmp)
{
	int		i;
	char	*tmp_s;

	i = -1;
	tmp_s = str_replace(ms, str, NULL, NULL);
	tmp_s = str_replace2(ms, tmp_s, tmp, -1);
	if (tmp_s == NULL)
		return (err("export", str, ms, 0));
	len = is_plus(ms, len, 1);
	while (ms->envp && ms->envp[++i])
	{
		if (ft_strncmp(tmp[i], tmp_s, len) == 0)
		{
			len = is_plus(ms, len, 0);
			if (str[len] == '=')
			{
				free(ms->envp[i]);
				ms->envp[i] = ft_strdup(tmp_s);
			}
			free(tmp_s);
			return (0);
		}
	}
	append2(ms, i, tmp, tmp_s);
	return (0);
}

char	**caching(char **str)
{
	int		i;
	char	**tmp;

	if (!str)
	{
		tmp = malloc(sizeof(char *));
		tmp[0] = NULL;
		return (tmp);
	}
	i = 0;
	while (str && str[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str && str[i])
	{
		tmp[i] = ft_strdup(str[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	ft_export4(t_ms *ms, char **str, char **tmp, int i)
{
	int	j;

	j = 0;
	while (str && str[i])
	{
		j = 0;
		tmp = caching(ms->envp);
		while (str && str[i] && str[i][j] && str[i][j] != '=')
			j++;
		append(ms, j, str[i], tmp);
		doublefree(tmp);
		i++;
	}
}

int	ft_export(t_ms *ms, char **str, int i)
{
	int		test;

	if (!str[i])
		return (1);
	while (str && str[i])
	{
		test = ft_export2(ms, str, i);
		if (test == 1 || test == 0)
			i++;
		else if (test == 2)
			return (0);
		else if (test == 3)
			return (1);
	}
	if (!ms->envp)
		return (ft_export_env(ms, str, i));
	ft_export4(ms, str, NULL, 1);
	return (0);
}

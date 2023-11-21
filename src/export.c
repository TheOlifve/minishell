/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/09 18:39:15 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *str, t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (1);
	j = check_var2(str);
	if (j == -1)
	{
		err("export", str, ms, 0);
		return (3);
	}
	else if (j == -2)
		return (2);
	else if (j == -3)
		return (0);
	else if (check_var3(str, i, j, ms) != 0)
		return (3);
	return (0);
}

char	*str_replace(char *str)
{
	int		i;
	int		j;
	char	*str2;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '+')
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
	{
		str2 = ft_strdup(str);
		j = i + 1;
		while (str[j])
		{
			str[i] = str2[j];
			i++;
			j++;
		}
		str[i] = '\0';
	}
	return (str);
}

int	append(t_ms *ms, int len, char *str, char **tmp)
{
	int		i;

	i = 0;
	str = str_replace(str);
	while (ms->envp && ms->envp[i])
	{
		if (ft_strncmp(tmp[i], str, len + 1) == 0)
		{
			ms->envp[i] = malloc(sizeof(char *));
			ms->envp[i] = ft_strdup(str);
			return (0);
		}
		i++;
	}
	free(ms->envp);
	ms->envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tmp && tmp[i])
	{
		ms->envp[i] = ft_strdup(tmp[i]);
		i++;
	}
	ms->envp[i] = ft_strdup(str);
	ms->envp[i + 1] = NULL;
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

int	ft_export(t_ms *ms, char **str, int i, int j)
{
	int		test;
	char	**tmp;

	tmp = NULL;
	if (!str[i])
		return (1);
	test = ft_export2(ms, str, i);
	if (test == 1)
	{
		i++;
		ft_export(ms, str, i, 0);
	}
	else if (test == 2)
		return (0);
	else if (test == 3)
		return (1);
	if (!ms->envp)
		return (ft_export_env(ms, str, i));
	tmp = caching(ms->envp);
	while (str[i] && str[i][j] != '=')
		j++;
	append(ms, j, str[i], tmp);
	free(tmp);
	return (0);
}

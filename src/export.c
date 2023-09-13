/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/08/31 11:57:39 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_var2(char *str)
{
	int		i;
	int		len;

	i = 0;
	if ((str[i] > 64 && str[i] < 91)
			|| (str[i] > 96 && str[i] < 123)
				|| (str[i] == '_'))
		;
	else
		return (-1);
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	if ((str[i] == '=' && str[i + 1] == '\0') ||
			(str[i] != '='))
		return (-2);
	if (len < 3)
		return (-1);
	if (str[i] && ((str[i - 1] && str[i - 1] == 32) ||
			(str[i + 1] && str[i + 1] == 32)))
		return (-1);
	return (i);
}

int	check_var(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (1);
	j = check_var2(str);
	if (j == -1)
		return (ERR("export", str));
	else if (j == -2)
		return (1);
	while (str && str[i] && i <= j)
	{
		if (((str[i] > 64 && str[i] < 91)
				|| (str[i] > 96 && str[i] < 123)
				|| (str[i] > 47 && str[i] < 58))
				|| (str[i] == '=') || (str[i] == '+' &&
				str[i + 1] == '=' )|| str[i] == '_')
				i++;
		else
			return (ERR("export", str));
	}
	return (0);
}

int	append(t_ms *ms, int len, char *str, char **tmp)
{
	int		i;

	i = 0;
	while (ms->cache && ms->cache[i])
	{
		if (ft_strncmp(tmp[i], str, len + 1) == 0)
		{
			free(ms->cache[i]);
			ms->cache[i] = malloc(sizeof(char *));
			ms->cache[i] = ft_strdup(str);
			return (0);
		}
		i++;
	}
	free(ms->cache);
	ms->cache = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tmp && tmp[i])
	{
		ms->cache[i] = tmp[i];
		i++;
	}
	ms->cache[i] = ft_strdup(str);
	ms->cache[i + 1] = NULL;
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

int	ft_export(t_ms *ms, char *str)
{
	int		i;
	char	**tmp;

	tmp = NULL;
	i = 0;
	if (check_var(str) == 0)
		;
	else
		return (1);
	if (!ms->cache)
	{
		ms->cache = malloc(sizeof(char *) * 2);
		ms->cache[0] = ft_strdup(str);
		ms->cache[1] = NULL;
		printf("%s\n", ms->cache[0]);
		return (0);
	}
	tmp = caching(ms->cache);
	while (str && str[i] != '=')
		i++;
	append(ms, i, str, tmp);
	i = 0;
	while (ms->cache && ms->cache[i])
	{
		printf("%s\n", ms->cache[i]);
		i++;
	}
	free(tmp);
	return (0);
}

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
	while (ms->envp && ms->envp[i])
		i++;
	free(ms->envp);
	ms->envp = malloc(sizeof(char *) * i);
	ms->envp[i - 1] = NULL;
	i = 0;
	while (tmp && tmp[j] && ms->envp[i])
	{
		if (j != pos)
		{
			ms->envp[i] = tmp[j];
			i++;
			j++;
		}
		else
			j++;
	}
	return (0);
}

int	ft_unset2(t_ms *ms, char **str, int i)
{
	if (!str[i])
			return (0);
	(void)ms;
	if (check_var1(str[i]) == 0)
	{
		i++;
		ft_unset(ms, str, i);
	}
	else
		return (1);
	return (0);
}

int	ft_unset(t_ms *ms, char **str, int i)
{
	int		j;
	char	*str2;
	char	**tmp;

	if (!str[i])
		return (1);
	if (ft_unset2(ms, str, i) == 1)
	{
		i++;
		ft_unset(ms, str, i);
	}
	if (!ms->envp)
		return (1);
	str2 = ft_strdup(str[i]);
	free(str[i]);
	str[i] = ft_strjoin(str2, "=");
	free(str2);
	tmp = caching(ms->envp);
	j = -1;
	while (tmp && tmp[++j])
	{
		if (ft_strncmp(tmp[j], str[i], ft_strlen(str[i])) == 0)
			ft_remove(ms, j, tmp);
	}
	return (0);
}

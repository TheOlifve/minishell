/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/07 22:30:43 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	if (str[j] == '=' && str[j + 1] == '\0')
		return (1);
	if ((str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i] < 122))
		i++;
	while (str && str[i] && i <= j)
	{
		if (((str[i] > 64 && str[i] < 91)
				|| (str[i] > 96 && str[i] < 122)
				|| (str[i] > 47 && str[i] < 58))
				|| (str[i] == '='))
				i++;
		else
			return (1);
	}
	return (0);
}

void	writ_to_file(t_ms *ms, char *str, int i, char *tmp)
{
	char	*tmp2;

	ms->ex_tmp = ft_strdup("");
	while (tmp)
	{
		if (!ft_strncmp(tmp, str, i))
		{
			free(tmp);
			tmp = ft_strdup("");
		}
		tmp2 = ft_strjoin(ms->ex_tmp, tmp);
		if (ms->ex_tmp)
			free(ms->ex_tmp);
		ms->ex_tmp = ft_strdup(tmp2);
		free(tmp);
		free(tmp2);
		tmp = get_next_line(ms->cache);
	}
	tmp = ft_strjoin(ms->ex_tmp, str);
	free(ms->ex_tmp);
	unlink("cache");
	ms->cache = open("cache", O_RDWR | O_APPEND | O_CREAT, 0644);
	write(ms->cache, tmp, ft_strlen(tmp));
	write(ms->cache, "\n", 1);
	free(tmp);
}

int	ft_export(t_ms *ms, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	if (len == 0 || len == 1 || len == 2)
		return (1);
	if (str[i] && ((str[i - 1] && str[i - 1] == 32) ||
			(str[i + 1] && str[i + 1] == 32)))
		return (1);
	if (check_var(str) == 0)
		ms->cache = open("cache", O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		return (1);
	if (ms->cache < 0)
		return (1);
	writ_to_file(ms, str, i, get_next_line(ms->cache));
	return (0);
}


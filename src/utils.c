/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:12:25 by rugrigor          #+#    #+#             */
/*   Updated: 2023/08/29 13:34:13 by rugrigor         ###   ########.fr       */
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

void	check_dol(t_ms *ms)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 0;
	j = -1;
	while (ms->str && ms->str[i])
	{
		j = -1;
		while (ms->str && ms->str[i] && ms->str[i][++j])
		{
			if (ms->str[i][j] == '$')
			{
				tmp = dol_check(ms, ms->str[i]);
				tmp2 = trim_dol(ms->str[i]);
				free(ms->str[i]);
				ms->str[i] = ft_strjoin(tmp2, tmp);
			}
		}
		i++;
	}
}

int	get_cmd(char *path, char *cmd)
{
	int	i;
	int	j;

	if (path == NULL)
		return (0);
	i = ft_strlen(path) - 1;
	j = ft_strlen(cmd) - 1;
	if (i < j)
		return (0);
	while (j >= 0 && i >= 0)
	{
		if (path && cmd && path[i] != cmd[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}
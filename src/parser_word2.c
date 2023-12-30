/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/12/06 12:01:45 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	doublefree(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*cmd_build(t_ms *ms, char *word)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**path;

	if (!word)
		return (NULL);
	i = -1;
	path = ft_split(ms->path, ':');
	tmp = ft_strjoin("/", word);
	while (path && path[++i])
	{
		tmp2 = ft_strjoin(path[i], tmp);
		if (access(tmp2, X_OK) == 0)
		{
			doublefree(path);
			free(tmp);
			return (tmp2);
		}
		free(tmp2);
	}
	doublefree(path);
	free(tmp);
	return (NULL);
}

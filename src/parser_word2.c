/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <hrahovha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/09/07 22:30:43 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			free(path);
			free(tmp);
			return (tmp2);
		}
		free(tmp2);
	}
	free(path);
	free(tmp);
	return (NULL);
}

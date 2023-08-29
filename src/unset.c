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

void	del_from_file(t_ms *ms, char *str, char *tmp)
{
	char	*tmp2;

	while (tmp)
	{
		if (!ft_strncmp(tmp, str, ft_strlen(str)))
			;
		else
		{
			tmp2 = ft_strjoin(ms->us_tmp, tmp);
			if (ms->us_tmp)
				free(ms->us_tmp);
			ms->us_tmp = ft_strdup(tmp2);
			free(tmp);
			free(tmp2);
		}
		tmp = get_next_line(ms->cache);
	}
	unlink("cache");
	ms->cache = open("cache", O_RDWR | O_APPEND | O_CREAT, 0644);
	write(ms->cache, ms->us_tmp, ft_strlen(ms->us_tmp));
	write(ms->cache, "\n", 1);
	free(ms->us_tmp);
}

int	ft_unset(t_ms *ms, char *str)
{
	char	*tmp;

	ms->cache = open("cache", O_RDWR | O_APPEND | O_CREAT, 0644);
	if (ms->cache < 0)
		return (1);
	tmp = get_next_line(ms->cache);
	ms->us_tmp = ft_strdup("");
	del_from_file(ms, str, tmp);
	return (0);
}

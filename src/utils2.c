/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:11:50 by rugrigor          #+#    #+#             */
/*   Updated: 2023/10/30 15:43:50 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_concat(char *cmd, char *opt)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**option;

	i = 0;
	if (!cmd)
		cmd = ft_strdup("");
	tmp2 = ft_strdup(cmd);
	free(cmd);
	option = ft_split(opt, ' ');
	while (option && option[i])
	{
		tmp = ft_strdup(tmp2);
		free(tmp2);
		tmp2 = ft_strjoin(tmp, option[i]);
		free(tmp);
		i++;
	}
	cmd = ft_strjoin(tmp2, " ");
	free(tmp2);
	free(option);
	return (cmd);
}

void	goto_start(t_ms *ms)
{
	while (ms->tree[ms->ord])
	{
		if(ms->tree[ms->ord]->prev)
			ms->tree[ms->ord] = ms->tree[ms->ord]->prev;
		else
			break;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:11:50 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/08 20:16:57 by rugrigor         ###   ########.fr       */
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

// char	*hard_bon_help(t_ms *m, char *str, char *ptr, int n)
// {
// 	n++;
// 	ptr = ft_strjoin(str, m->scope2);
// 	if (n == 1)
// 	ptr = ft_strjoin(str, m->scope);
// 	free(str);
// 	return (ptr);
// }

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
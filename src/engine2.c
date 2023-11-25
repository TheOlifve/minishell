/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:10:06 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/24 23:56:45 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	bonus_file(t_ms *ms)
{
	if (ms->tree[ms->ord])
			goto_start(ms);
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->_redir)
			open_files(ms, ft_split(ms->tree[ms->ord]->_redir, ' '), 0);
		ms->ord += 1;
	}
	return (0);
}

char	*cmd_builder(t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	goto_start(ms);
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->_cmd != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_cmd);
		if (ms->tree[ms->ord]->_option != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_option);;
		if (ms->tree[ms->ord]->_file != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_file);;
		if (ms->tree[ms->ord]->_word != NULL)
			ft_concat(ms, ms->tree[ms->ord]->_word);;
		if (ms->tree[ms->ord]->next)
			ms->tree[ms->ord] = ms->tree[ms->ord]->next;
		else
			break ;
	}
	goto_start(ms);
	tmp = ft_strdup(ms->my_cmd);
	free(ms->my_cmd);
	ms->my_cmd = NULL;
	return (tmp);
}

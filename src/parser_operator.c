/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/20 14:56:05 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*redir_build(t_ms *ms, char *opr)
{
	char	*tmp;
	char	*tmp2;

	if (ms->tree[ms->ord]->_redir != NULL)
	{
		tmp = ft_strjoin(ms->tree[ms->ord]->_redir, " ");
		tmp2 = ft_strjoin(tmp, opr);
		free(ms->tree[ms->ord]->_redir);
		free(tmp);
		return (tmp2);
	}
	// ms->bool_word += 1;
	tmp2 = ft_strdup(opr);
	return (tmp2);
}

int	opr_cmp(char *opr)
{
	if (opr[0] == '>' || opr[0] == '<')
		return (0);
	else if (opr[0] == '|' && !opr[1])
		return (1);
	else if (opr[0] == '&')
		return (2);
	else
		return (3);
}

void	operator_distribute2(t_ms *ms, int type, char *opr)
{
	if (type == 0)
	{
		if (ms->bool_word == 0)
			ms->tree[ms->ord] = tree_new();
		goto_start(ms);
		ms->tree[ms->ord]->_redir = redir_build(ms, opr);
	}
	if (type == 1)
	{
		if (ms->bool_word == 0)
			ms->tree[ms->ord] = tree_new();
		goto_start(ms);
		ms->tree[ms->ord]->_pipe = ft_strdup("|");
	}
	else if (type == 2)
		ms->tree[ms->ord]->_and = ft_strdup("&&");
	else if (type == 3)
		ms->tree[ms->ord]->_or = ft_strdup("||");
	if (type == 1 || type == 2 || type == 3)
	{
		ms->ord++;
		ms->bool_word = 0;
		tree_add_back(&ms->tree[ms->ord], tree_new());
	}
}

int	operator_distribute(t_ms *ms, char *opr)
{
	int		type;

	if (ms->bool_word == 0 && (opr[0] == '|' || opr[0] == '&'))
		return (pars_err(opr, ms));
	if (!ms->tree[ms->ord])
		ms->tree[ms->ord] = tree_new();
	type = opr_cmp(opr);
	operator_distribute2(ms, type, opr);
	goto_start(ms);
	return (0);
}

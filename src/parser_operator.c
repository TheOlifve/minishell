/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/10/30 15:40:56 by rugrigor         ###   ########.fr       */
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
	ms->bool_word += 1;
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

int	operator_distribute2(t_ms *ms, int type, char *opr)
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
		ms->tree[ms->ord]->_pipe = ft_strdup("|");
		ms->ord++;
		ms->bool_word = 0;
		tree_add_back(&ms->tree[ms->ord], tree_new());
	}
	else if (type == 2)
	{
		ms->tree[ms->ord]->_and = ft_strdup("&&");
		ms->ord++;
		ms->bool_word = 0;
		tree_add_back(&ms->tree[ms->ord], tree_new());
	}
	else if (type == 3)
	{
		ms->tree[ms->ord]->_or = ft_strdup("||");
		ms->bool_word = 0;
		ms->ord++;
		tree_add_back(&ms->tree[ms->ord], tree_new());
	}
	return (0);
}

int	operator_distribute(t_ms *ms, char *opr) // > or < = 0 | pipe = 1 | and = 2 | or = 3
{
	int		type;

	if (ms->bool_word == 0 && (opr[0] == '|' || opr[0] == '&'))
		return (pars_err(opr, ms));
	if (!ms->tree[ms->ord])
		ms->tree[ms->ord] =  tree_new();
	type = opr_cmp(opr);
	operator_distribute2(ms, type, opr);
	goto_start(ms);
	return (0);
}

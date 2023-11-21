/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/20 12:27:01 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	spaces(t_ms *ms, int i)
{
	char	*ptr;

	ptr = ft_strdup(ms->args);
	while (ptr && ptr[++i])
		if (ptr[i] == '\t')
			ptr[i] = 32;
	i = 0;
	while (ptr && ptr[i] != '\0')
	{	
		if (ptr[i] != 32)
		{
			free(ptr);
			return (0);
		}
		i++;
	}
	free(ptr);
	return (1);
}

int	parser(t_lexer *lexer, t_ms *ms)
{
	ms->tree[ms->ord] = tree_new();
	while (lexer)
	{
		if (ft_strcmp(lexer->id, "word\0") == 0)
		{
			word_distribute(&lexer, ms, lexer->kw);
			if (ms->tree[ms->ord]->next)
				ms->tree[ms->ord] = ms->tree[ms->ord]->next;
		}
		else if (ft_strcmp(lexer->id, "operator\0") == 0)
			operator_distribute(ms, lexer->kw);
		if (lexer->next)
			lexer = lexer->next;
		else
			break ;
	}
	ms->ord = 0;
	return (0);
}
	// while (ms->tree[ms->ord])
	// {
	// 	goto_start(ms);
	// 	while (ms->tree[ms->ord])
	// 	{
	// 		printf("cmd - %s\noption - %s\nfile - %s\nword - %s\nredir - %s\npipe - %s\nand - %s\nor - %s\n",ms->tree[ms->ord]->_cmd,ms->tree[ms->ord]->_option,
	// 		ms->tree[ms->ord]->_file,ms->tree[ms->ord]->_word,
	// 		ms->tree[ms->ord]->_redir,ms->tree[ms->ord]->_pipe,
	// 		ms->tree[ms->ord]->_and,ms->tree[ms->ord]->_or);
	// 		printf("_____________________________________________________\n");
	// 		ms->tree[ms->ord] = ms->tree[ms->ord]->next;
	// 	}
	// 	ms->ord++;
	// } 
	// ms->ord = 0;

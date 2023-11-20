/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/20 16:01:45 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*hard_bon_help(t_ms *m, int n, char *str, char *str2)
{
	char	*ptr;

	if (n == 1)
		ptr = ft_strjoin(str, m->scope);
	else
		ptr = ft_strjoin(str, m->scope2);
	free(str);
	str = ft_strjoin(ptr, str2);
	free(ptr);
	free(str2);
	ptr = ft_strdup(str);
	free(str);
	return (ptr);
}

void	prior2(char *ptr, t_lexer **lexer, int x, int n)
{
	int	i;

	i = 0;
	(*lexer)->kw = (char *)malloc(sizeof(char) * (ft_strlen(ptr) - x + 1));
	while (ptr[n])
	{
		if (ptr[n] == 4)
			n++;
		(*lexer)->kw[i] = ptr[n];
		i++;
		n++;
	}
	(*lexer)->kw[i] = '\0';
	free(ptr);
}

void	prior(t_lexer **lexer, int i, int x)
{
	char	*ptr;

	ptr = NULL;
	while (*lexer && (*lexer)->kw && (*lexer)->kw[++i])
	{
		if ((*lexer)->kw[i] == '(' || (*lexer)->kw[i] == ')')
		{
			(*lexer)->kw[i] = 4;
			x++;
		}
	}
	ptr = ft_strdup((*lexer)->kw);
	free((*lexer)->kw);
	prior2(ptr, lexer, x, 0);
}

int	parser(t_lexer *lexer, t_ms *ms)
{
	ms->tree[ms->ord] = tree_new();
	while (lexer)
	{
		// prior(&lexer, -1, 0);
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
	return (0);
}

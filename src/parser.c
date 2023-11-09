/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/09 14:32:36 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	scope2(t_ms *ms, char *ptr)
// {
// 	int		i;
// 	char	**str;

// 	i = -1;
// 	while (ms->scope[++i])
// 		;
// 	str = (char **)malloc(sizeof(char *) * (i + 2));
// 	i = -1;
// 	while (ms->scope[++i])
// 		str[i] = ft_strdup(ms->scope[i]);
// 	str[i] = ptr;
// 	str[i + 1] = NULL;
// 	free(ms->scope);
// 	ms->scope = str;
// 	free(str);
// }

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
		// if ((*lexer)->kw[i] == '(' && (ms->prior == 4
		// 	|| ms->prior == 2))
		// 	ms->prior = 1;
		// if ((*lexer)->kw[i] == ')' && ms->prior == 1)
		// 	ms->prior = 2;
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


// void	scope(t_ms *ms, t_lexer **lexer)
// {
// 	int		i;
// 	int		x;
	
// 	i = -1;
// 	x = 1;
	// while ((*lexer)->kw[++i])
	// {
	// 	if ((*lexer)->kw[i] == '(' || (*lexer)->kw[i] == ')')
	// 	{
	// 		if (!ms->scope)
	// 		{
	// 			ms->scope = (char **)malloc(sizeof(char *) * 2);
	// 			ms->scope[0] = ft_itoa(ms->ord);
	// 			ms->scope[x] = NULL;
	// 		}
	// 		else
	// 			scope2(ms, ft_itoa(ms->ord));
	// 	}
	// }
// 	prior(lexer, -1, 0);
// }

int	parser(t_lexer *lexer, t_ms *ms)
{
	ms->tree[ms->ord] = tree_new();
	while (lexer)
	{
		prior(&lexer, -1, 0);
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

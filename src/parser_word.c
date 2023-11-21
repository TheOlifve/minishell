/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:32:34 by hrahovha          #+#    #+#             */
/*   Updated: 2023/11/21 19:08:05 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*option_build(t_lexer **lexer, char *word)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(word);
	while (lexer)
	{
		if ((*lexer)->next)
			*lexer = (*lexer)->next;
		else
			return (tmp);
		if (ft_strncmp((*lexer)->kw, "-", 1) == 0)
		{
			(*lexer)->kw++;
			tmp2 = ft_strjoin(tmp, (*lexer)->kw);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		else
		{
			*lexer = (*lexer)->prev;
			return (tmp);
		}
	}
	return (tmp);
}

void	doublefree(char **str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	word_cmp2(t_ms *ms, char *word)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**path;

	i = -1;
	path = ft_split(ms->path, ':');
	tmp = ft_strjoin("/", word);
	while (path && path[++i])
	{
		tmp2 = ft_strjoin(path[i], tmp);
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			doublefree(path);
			free(tmp2);
			return (1);
		}
		free(tmp2);
	}
	free(tmp);
	doublefree(path);
	if (access(word, F_OK) == 0)
		return (3);
	return (4);
}

int	word_cmp(t_ms *ms, char *word)
{
	if (ft_strcmp(word, "cd") == 0 || ft_strcmp(word, "pwd") == 0
		|| ft_strcmp(word, "env") == 0 || ft_strcmp(word, "echo") == 0
		|| ft_strcmp(word, "exit") == 0 || ft_strcmp(word, "unset") == 0
		|| ft_strcmp(word, "export") == 0 || ft_strncmp(word, "./", 2) == 0)
		return (0);
	else if (ft_strcmp(word, "..") == 0 || ft_strcmp(word, ".") == 0)
		return (5);
	else if (word[0] == '-')
		return (2);
	return (word_cmp2(ms, word));
}

int	word_distribute2(t_lexer **lexer, t_ms *ms, char *word, int type)
{
	if (type == 2 && ms->bool_word == 1)
		ms->tree[ms->ord]->_option = option_build(lexer, word);
	else
	{
		tree_add_back(&ms->tree[ms->ord], tree_new());
		ms->tree[ms->ord] = ms->tree[ms->ord]->next;
		if (type == 0 || type == 1 || type == 2 || type == 3)
			ms->tree[ms->ord]->_file = ft_strdup(word);
		else if (type == 4 || type == 5 || type == 0)
			ms->tree[ms->ord]->_word = ft_strdup(word);
	}
	return (0);
}

int	word_distribute(t_lexer **lexer, t_ms *ms, char *word)
{
	int	type;

	type = word_cmp(ms, word);
	if (ms->bool_word == 0)
	{
		if (!ms->tree[ms->ord])
			ms->tree[ms->ord] = tree_new();
		if (type == 1 && !ms->tree[ms->ord]->_cmd)
			ms->tree[ms->ord]->_cmd = cmd_build(ms, word);
		else if (!ms->tree[ms->ord]->_cmd)
			ms->tree[ms->ord]->_cmd = ft_strdup(word);
	}
	else
		word_distribute2(lexer, ms, word, type);
	ms->bool_word++;
	return (0);
}

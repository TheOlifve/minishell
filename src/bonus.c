/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:40:23 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/30 22:08:58 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*word_cmp3(t_ms *ms, char *word)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**path;

	i = -1;
	if (check_built(word))
		return (word);
	path = ft_split(ms->path, ':');
	tmp = ft_strjoin("/", word);
	while (path && path[++i])
	{
		tmp2 = ft_strjoin(path[i], tmp);
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			doublefree(path);
			free(word);
			return (tmp2);
		}
		free(tmp2);
	}
	free(tmp);
	doublefree(path);
	return (word);
}

char	*priority(t_ms *ms, char *ptr, int i, int n)
{
	while (ptr && ptr[++i] && ms->prior != 4)
	{
		if (ms->prior == 1)
			ms->prior = 2;
		if (ptr[i] == '(' && ptr[i + 1] == '(')
		{
			ms->prior = 7;
			while (ptr && ptr[++i] && ms->prior != 1)
			{
				if (ptr[i] == ')' && ptr[i + 1] != ')')
					ms->prior = 1;
				if (ptr[i] == ')' && ptr[i + 1] == ')')
					break ;
			}
			break ;
		}
		if (ms->prior == 0 && ptr[i] == '(' && ptr[i + 1] != '(')
			ms->prior = 1;
		else if (ms->prior == 1 && (ptr[i] != '(' || ptr[i] != ')'))
			ms->prior = 2;
		else if (ms->prior == 2 && ptr[i] == ')')
			ms->prior = 4;
	}
	return (priority2(ms, ptr, NULL, n));
}

void	eng3(t_ms *ms)
{
	if (ms->prior == 5)
		ms->prior = 0;
	if (ms->prior == 0 && access("bonus_help", F_OK) == 0)
	{
		close(ms->bonus);
		unlink("bonus_help");
	}
}

void	eng2(t_ms *ms, int n)
{
	eng3(ms);
	while (ms->tree[n])
	{
		if (ms->tree[n]->_redir && !ms->tree[n]->_pipe)
			file_cmd(ms, -1, NULL);
		if (ms->tree[n]->_cmd)
			ms->tree[n]->_cmd = word_cmp3(ms,
					priority(ms, ms->tree[n]->_cmd, -1, n));
		if (ms->tree[n]->_option)
			ms->tree[n]->_option = priority(ms, ms->tree[n]->_option, -1, n);
		if (ms->tree[n]->_redir)
			ms->tree[n]->_redir = priority(ms, ms->tree[n]->_redir, -1, n);
		if (ms->tree[n]->_file)
			ms->tree[n]->_file = priority(ms, ms->tree[n]->_file, -1, n);
		if (ms->tree[n]->_word)
			ms->tree[n]->_word = priority(ms, ms->tree[n]->_word, -1, n);
		if (!ms->tree[n]->_pipe)
			break ;
		n++;
	}
	if (access("bonus_help", F_OK) != 0 && ms->prior > 0)
		ms->bonus = open("bonus_help", O_RDWR | O_APPEND | O_CREAT, 0644);
}

int	eng(t_ms *ms)
{
	int	n;
	int	x;

	n = ms->ord;
	x = ms->ord;
	ms->index = ms->ord;
	eng2(ms, n);
	if (ms->prior == 4 && ms->bonus2 > 0 && ms->x != 2)
	{
		ms->c1 = 1;
		ms->c2 = ms->bonus2;
		ms->bonus2 = 0;
	}
	while (ms && ms->tree[x])
	{
		if (ms->tree[x]->_or)
			return (x);
		x++;
	}
	return (-1);
}

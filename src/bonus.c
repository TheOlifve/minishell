/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:40:23 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/21 15:24:26 by hrahovha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*priority3(char *str, char *ptr, int i, int x)
{
	int	n;

	n = -1;
	str = (char *)malloc(sizeof(char) * (ft_strlen(ptr) - x + 4));
	i = 0;
	while (ptr && ptr[++n])
	{
		if (ptr[n] == 4)
		{
			n++;
			if (!ptr[n])
				break ;
		}
		str[i] = ptr[n];
		i++;
	}
	str[i] = '\0';
	free(ptr);
	return (str);
}

char	*priority2(char *str, char *ptr, int i, int x)
{
	while (str && str[++i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			str[i] = 4;
			x++;
		}
	}
	ptr = ft_strdup(str);
	free(str);
	return (priority3(NULL, ptr, 0, x));
}

char	*priority(t_ms *ms, char *ptr, int i)
{
	while (ptr && ptr[++i])
	{
		if (ms->prior == 1)
			ms->prior = 2;
		if (ptr[i] == '(' && ptr[i + 1] == '(')
		{
			ms->prior = 7;
			while (ptr && ptr[++i])
			{
				if (ptr[i] == ')' && ptr[i + 1] != ')')
					ms->prior = 1;
				if ((ptr[i] == ')' && ptr[i + 1] != ')')
					|| (ptr[i] == ')' && ptr[i + 1] == ')'))
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
	return (priority2(ptr, NULL, -1, 0));
}

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
			free(path);
			free(word);
			return (tmp2);
		}
		free(tmp2);
	}
	free(tmp);
	free(path);
	return (word);
}

int	eng(t_ms *ms)
{
	int	n;

	n = ms->ord;
	ms->index = ms->ord;
	if (ms->prior == 0 && access("bonus_help", F_OK) == 0)
		unlink("bonus_help");
	if (ms->tree[n]->_cmd)
		ms->tree[n]->_cmd = word_cmp3(ms, priority(ms, ms->tree[n]->_cmd, -1));
	if (ms->tree[n]->_option)
		ms->tree[n]->_option = priority(ms, ms->tree[n]->_option, -1);
	if (ms->tree[n]->_redir)
		ms->tree[n]->_redir = priority(ms, ms->tree[n]->_redir, -1);
	if (ms->tree[n]->_file)
		ms->tree[n]->_file = priority(ms, ms->tree[n]->_file, -1);
	if (ms->tree[n]->_word)
		ms->tree[n]->_word = priority(ms, ms->tree[n]->_word, -1);
	while (ms && ms->tree[n])
	{
		if (ms->tree[n]->_or)
			return (n);
		n++;
	}
	return (-1);
}

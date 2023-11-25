/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:40:23 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/23 15:19:27 by hrahovha         ###   ########.fr       */
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

void	file_cmd(t_ms *ms, int i, int j, char *tmp)
{
	char	**file;
	
	file = ft_split(ms->tree[ms->ord]->_redir, ' ');
	
	while (ms->tree[ms->ord]->_redir && file[++i] && ms->bonus2 == 0)
	{
		printf("aaa\n");
		while (file[i] && file[i][++j] && ms->bonus2 == 0)
		{
			if (file[i] && file[i][j] != ')' && file[i][j + 1] == ')')
			{
				tmp = ft_strtrim(ft_strdup(file[i]), ")");
				printf("%s\n", tmp);
				if (ft_strncmp(file[i], ">>", 2) == 0 && file[i] != NULL)
					ms->bonus2 = open(tmp + 2, O_RDWR | O_APPEND | O_CREAT, 0644);
				else if (ft_strncmp(file[i], ">", 1) == 0 && file[i] != NULL)
					ms->bonus2 = open(tmp + 1, O_RDWR | O_TRUNC | O_CREAT, 0644);
				free(tmp);
				break ;
			}
		}
	}
	i = -1;
	while (ms->tree[ms->ord]->_redir && file[++i])
		free(file[i]);
	if (ms->tree[ms->ord]->_redir)
		free(file);
}

void	eng2(t_ms *ms, int n)
{
	if (ms->prior == 5)
		ms->prior = 0;
	if (ms->prior == 0 && access("bonus_help", F_OK) == 0)
	{
		close(ms->bonus);
		unlink("bonus_help");
	}
	while (ms->tree[n])
	{
		if (ms->tree[n]->_redir && !ms->tree[n]->_pipe)
			file_cmd(ms, -1, -1, NULL);
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
	while (ms && ms->tree[x])
	{
		if (ms->tree[x]->_or)
			return (x);
		x++;
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:28:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/11/22 02:19:59 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo2(t_ms *ms)
{
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->_word)
		{
			printf("%s", ms->tree[ms->ord]->_word);
			if (ms->tree[ms->ord]->next)
				printf(" ");
		}
		else if (ms->tree[ms->ord]->_file)
		{
			printf("%s", ms->tree[ms->ord]->_file);
			if (ms->tree[ms->ord]->next)
				printf(" ");
		}
		ms->tree[ms->ord] = ms->tree[ms->ord]->next;
	}
}

int	echo(t_ms *ms, int i)
{
	int	n;

	n = 0;
	goto_start(ms);
	while (ms && ms->tree[ms->ord] && ms->tree[ms->ord]->_option
		&& ms->tree[ms->ord]->_option[++n])
		if (ms->tree[ms->ord]->_option[n] != 'n')
			i = 1;
	if (!ms->tree[ms->ord]->_option)
		i = 1;
	if (i == 1 && ms->tree[ms->ord]->_option)
	{
		printf("%s", ms->tree[ms->ord]->_option);
		if (ms->tree[ms->ord]->next)
			printf(" ");
	}
	ms->tree[ms->ord] = ms->tree[ms->ord]->next;
	echo2(ms);
	if (i == 1)
		printf("\n");
	return (0);
}

int	pwd(t_ms *ms, int mod)
{
	int		i;
	char	buff[OPEN_MAX];
	char	*oldpwd;

	i = -1;
	getcwd(buff, OPEN_MAX);
	oldpwd = NULL;
	while (ms->envp[++i])
	{
		if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0)
		{
			oldpwd = ft_strdup(ms->envp[i]);
			ms->envp[i] = ft_strjoin("PWD=", buff);
			break ;
		}
	}
	if (mod == 1)
		printf("%s\n", buff);
	else
		ms->envp[i + 1] = ft_strjoin("OLD", oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (0);
}

int	env(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->envp && ms->envp[i])
	{
		printf("%s\n", ms->envp[i]);
		i++;
	}
	return (0);
}

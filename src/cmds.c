/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:28:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/12/22 11:41:08 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo2(t_ms *ms)
{
	while (ms->tree[ms->ord])
	{
		if (ms->tree[ms->ord]->_word)
		{
			ex_1(&ms->tree[ms->ord]->_word, -1, -1);
			printf("%s", ms->tree[ms->ord]->_word);
			if (ms->tree[ms->ord]->next)
				printf(" ");
		}
		else if (ms->tree[ms->ord]->_file)
		{
			ex_1(&ms->tree[ms->ord]->_file, -1, -1);
			printf("%s", ms->tree[ms->ord]->_file);
			if (ms->tree[ms->ord]->next)
				printf(" ");
		}
		if (ms->tree[ms->ord]->next)
			ms->tree[ms->ord] = ms->tree[ms->ord]->next;
		else
			break ;
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
		ex_1(&ms->tree[ms->ord]->_option, -1, -1);
		printf("%s", ms->tree[ms->ord]->_option);
		if (ms->tree[ms->ord]->next)
			printf(" ");
	}
	if (ms->tree[ms->ord]->next)
		ms->tree[ms->ord] = ms->tree[ms->ord]->next;
	echo2(ms);
	if (i == 1)
		printf("\n");
	return (0);
}

char	*pwd3(t_ms *ms, char *buff)
{
	buff = getcwd(NULL, 0);
	if (buff == NULL)
		buff = pwd2(ms);
	return (buff);
}

int	pwd(t_ms *ms, int mod, int i, char *oldpwd)
{
	char	*buff;

	buff = pwd3(ms, NULL);
	while (ms->envp[++i])
	{
		if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0)
		{
			oldpwd = ft_strdup(ms->envp[i]);
			free (ms->envp[i]);
			ms->envp[i] = ft_strjoin("PWD=", buff);
			break ;
		}
	}
	if (mod == 1)
		printf("%s\n", buff);
	else
	{
		if (mod == 2)
			printf("%s\n", buff);
		free(ms->envp[i + 1]);
		ms->envp[i + 1] = ft_strjoin("OLD", oldpwd);
	}
	free(buff);
	free(oldpwd);
	return (0);
}

int	env(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->envp && ms->envp[i])
	{
		if (check_for_eq(ms->envp[i]) == 1)
			printf("%s\n", ms->envp[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:28:07 by rugrigor          #+#    #+#             */
/*   Updated: 2023/09/08 16:56:44 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(t_ms *ms, int i, int flag)
{
	int	n;

	n = -1;
	while (ms && ms->lcmd[i] && ms->lcmd[i]->flag && ms->lcmd[i]->flag[++n])
		if (ms->lcmd[i]->flag[n] != '-' && ms->lcmd[i]->flag[n] != 'n')
			flag = 1;
	if (!ms->lcmd[i]->flag)
		flag = 1;
	if (flag == 1 && ms->lcmd[i]->flag)
	{
		printf("%s", ms->lcmd[i]->flag);
		if (ms->lcmd[i]->next)
			printf(" ");
	}
	ms->lcmd[i] = ms->lcmd[i]->next;
	while (ms->lcmd[i])
	{
		if (ms->lcmd[i]->word)
		{
			printf("%s", ms->lcmd[i]->word);
			if (ms->lcmd[i]->next)
				printf(" ");
		}
		else if (ms->lcmd[i]->file)
		{
			printf("%s", ms->lcmd[i]->file);
			if (ms->lcmd[i]->next)
				printf(" ");
		}
		ms->lcmd[i] = ms->lcmd[i]->next;
	}
	if (flag == 1)
		printf("\n");
	return (0);
}

int	pwd(t_ms *ms, int mod)
{
	int		i;
	char	buff[256];
	char	*oldpwd;

	i = -1;
	if (getcwd(buff, 254) == NULL)
		return (1);
	oldpwd = NULL;
	while (ms->envp[++i])
	{
		if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0)
		{
			oldpwd = ft_strdup(ms->envp[i]);
			ms->envp[i] = ft_strjoin("PWD=", buff);
			break;
		}
	}
	if (mod == 1)
		printf("%s\n", buff);
	else
		ms->envp[i + 1] = ft_strjoin("OLD",oldpwd);
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
